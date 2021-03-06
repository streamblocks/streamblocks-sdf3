/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   xml.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   March 29, 2002
 *
 *  Function        :   XML interface functions
 *
 *  History         :
 *      29-03-02    :   Initial version.
 *      27-05-04    :   Changed datatypes to CAST datatypes.
 *      26-08-06    :   Additions by Bart Theelen.
 *      12-04-11    :   Add validation to libxml version.
 *
 * $Id: xml.cc,v 1.4.2.11 2010-08-15 19:30:04 mgeilen Exp $
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * In other words, you are welcome to use, share and improve this program.
 * You are forbidden to forbid anyone else to use, share and improve
 * what you give them.   Happy coding!
 */

#include "xml.h"
#include "../exception/exception.h"
#include "../tempfile/tempfile.h"
#include "../log/log.h"

/**
 * Error handler
 */
#define TMP_BUF_SIZE 256
void err(void *ctx, const char *msg, ...)
{
    char cstring[TMP_BUF_SIZE];
    int len = 0;
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    len = vsnprintf(cstring, TMP_BUF_SIZE, msg, arg_ptr);

    // strip of trailing newline.
    if (len > 0 && cstring[len - 1] == '\n')
        cstring[len - 1] = '\0';

    va_end(arg_ptr);
    logWarning(CString("XML: ") + (const char *)cstring);
}

/**
 * CValidate()
 *
 * First validates using DTD the xml file, and or schema file.
 *
 * Make libxml validate the xml file using the specified schema (xi:schema)
 * Errors are printed out to sderr using the default libxml error callback.
 * CValidate() also reports final result to stderr.
 *
 * @param doc The CDoc of the document we want to validate.
 * @return true if document is valid, false if invalid
 */
bool CValidate(CDoc *doc)
{

    if (doc == NULL)
    {
        logWarning("XML: No document specified (doc == NULL)");
        return false;
    }

    int res;
    if (xmlGetIntSubset(doc) != NULL)
    {
        /* Validate DTD */
        xmlValidCtxtPtr ctx = xmlNewValidCtxt();
        if (xmlValidateDocument(ctx, doc) == 0)
        {
            xmlFreeValidCtxt(ctx);
            return false;
        }
        xmlFreeValidCtxt(ctx);
    }

    CNode *root = CGetRootNode(doc);
    /* nothing to validate */
    if (root == NULL)
    {
        return true;
    }

    // hack to check if there is a schema file specified.
    // This hacks avoid that there is a warning.
    xmlChar *nsl = xmlGetProp(root, BAD_CAST"noNamespaceSchemaLocation");
    xmlChar *sl = xmlGetProp(root, BAD_CAST"schemaLocation");
    if (nsl == NULL && sl == NULL)
    {
        return true;
    }
    if (nsl) xmlFree(nsl);
    if (sl) xmlFree(sl);

    /* the XSD validation context */
    xmlSchemaValidCtxtPtr validationCtxt;


    /* A validation context created with NULL as the
     * @schema argument will validate the instance against the schemata
     * indicated by xsi:schemaLocation and xsi:noNamespaceSchemaLocation.
     */
    validationCtxt = xmlSchemaNewValidCtxt(NULL);
    if (validationCtxt == NULL)
    {
        logWarning("XML: Failed to create the validation context.");
        return false;
    }

    /* Validate the instance. */
    res = xmlSchemaValidateDoc(validationCtxt, doc);
    if (res == -1)
    {
        logWarning("XML: Internal error during validation.");
    }
    /* Cleanup */
    xmlSchemaFreeValidCtxt(validationCtxt);

    /* return result.*/
    return (res == 0);
}

/**
 * CParseFile ()
 * Open a file and parse it into a tree structure.
 */
CDoc *CParseFile(const CString &filename)
{
    xmlSetGenericErrorFunc(NULL, err);
    CDoc *doc = xmlReadFile(filename.c_str(), NULL, 0);

    if (doc != NULL)
    {

        if (!CValidate(doc))
        {
            logWarning("The document '" + filename + "' is not valid.");
        }
    }
    return doc;
}

/**
 * CSetPrivateDTD
 *
 * Set private (SYSTEM) dtd header on document.
 */
void CSetPrivateDTD(CDoc *doc, const CString &root_element, const CString &uri)
{
    xmlCreateIntSubset(doc,
                       BAD_CAST(const char *)root_element,
                       NULL,
                       BAD_CAST(const char *)uri);
}
/**
 * CNewDoc ()
 * Create a new document.
 */
CDoc *CNewDoc()
{
    CDoc *doc;

    doc = xmlNewDoc(BAD_CAST "1.0");
    return doc;
}


/**
 * CNewDoc ()
 * Create a new document.
 */
CDoc *CNewDoc(CNode *rootNode)
{
    CDoc *doc;

    doc = xmlNewDoc(BAD_CAST "1.0");
    xmlDocSetRootElement(doc, rootNode);

    return doc;
}

/**
 * CSaveFile ()
 * Output a document to a file.
 */
void CSaveFile(const CString &filename, CDoc *doc, int format)
{
    xmlSaveFormatFile(filename.c_str(), doc, format);
}

/**
 * CSaveFile ()
 * Output a document to a stream.
 */
void CSaveFile(ostream &out, CDoc *doc, int format)
{
    char c;

    // Temporary file
    CString tmpfile = tempFileName("", "sdf3");

    // Store XML document in temp file
    xmlSaveFormatFile(tmpfile, doc, format);

    // Read temp file to stream
    ifstream f(tmpfile);
    while (f.get(c) && !f.eof())
    {
        out << c;
    };
    f.close();

    // Remove temporary file
    remove(tmpfile);
}

/**
 * CGetRootNode ()
 * Get the root node of the document.
 */
CNode *CGetRootNode(CDoc *doc)
{
    return xmlDocGetRootElement(doc);
}

/**
 * CIsNode ()
 * Return name of node.
 */
CString CIsNode(const CNode *n)
{
    return CString((char *)n->name);
}

/**
 * CIsNode ()
 * Check that node has name 'name'.
 */
bool CIsNode(const CNode *n, const CString &name)
{
    if (!xmlStrcmp(n->name, (const xmlChar *) name.c_str()))
        return true;

    return false;
}

/**
 * CGetParentNode ()
 * Return pointer to parent of node.
 */
CNode *CGetParentNode(CNode *n)
{
    return n->parent;
}

/**
 * CGetChildNode ()
 * Return pointer to node with name 'name' (if exists).
 */
CNode *CGetChildNode(CNode *n, const CString &name)
{
    if (n == NULL)
        return NULL;

    // Check all children of node
    for (CNode *t = n->children; t != NULL; t = t->next)
    {
        // Compare name of node and searched name
        if (name.empty() || CIsNode(t, name))
        {
            // Found a child with correct name
            return t;
        }
    }

    // Did not find a child with correct name
    return NULL;
}

/**
 * CHasChildNode ()
 * Check that the node has a child with name 'name'.
 */
bool CHasChildNode(CNode *n, const CString &name)
{
    if (n == NULL)
        return false;

    // Check all children of node
    for (CNode *t = n->children; t != NULL; t = t->next)
    {
        // Compare name of node and searched name
        if (name.empty() || CIsNode(t, name))
        {
            // Found a child with correct name
            return true;
        }
    }

    // Did not find a child with correct name
    return false;
}

/**
 * CGetNodeContent ()
 * Return the content of a node as a string
 */
CString CGetNodeContent(CNode *n)
{
    CString contentStr;
    xmlChar *cont = xmlNodeGetContent(n);
    contentStr = (const char *) cont;
    xmlFree(cont);
    return contentStr;
}

/**
 * CAddNode ()
 * Add a child node to given node.
 */
CNode *CAddNode(CNode *n, const CString &name,
                const CString &content)
{
    CNode *r;

    if (n == NULL)
    {
        r = xmlNewNode(NULL, (const xmlChar *) name.c_str());
        xmlNodeSetContent(r, (const xmlChar *) content.c_str());
        return r;
    }

    // Add a child to the tree below node n
    r = xmlNewChild(n, NULL, (const xmlChar *) name.c_str(),
                    (const xmlChar *) content.c_str());

    return r;
}

/**
 * CAddNode ()
 * Add a child node to given node.
 */
CNode *CAddNode(CNode *n, const CString &name,
                const double content)
{
    char buf[256];

    // Convert content to string
    sprintf(buf, "%.10e", content);

    // Add node
    return CAddNode(n, name, CString(buf));
}

/**
 * CAddNode ()
 * Add a child node to given node.
 */
CNode *CAddNode(CNode *n, CNode *child)
{
    return xmlAddChild(n, child);
}

/**
 * CCopyNode ()
 * Create a copy of a node (including attributes and children).
 */
CNode *CCopyNode(CNode *n)
{
    return xmlCopyNode(n, 1);
}

/**
 * CNewNode ()
 * Create a new node.
 */
CNode *CNewNode(const CString &name)
{
    return xmlNewNode(NULL, (const xmlChar *)name.c_str());
}

/**
 * CRemoveNode ()
 * Remove a node and its children from the database.
 */
void CRemoveNode(CNode *n)
{
    // Unlink the node from the tree
    xmlUnlinkNode(n);

    // Free the memory for the subtree starting in this node
    xmlFreeNode(n);
}

/**
 * CReplaceNode ()
 * Replace node with new node (old node is returned).
 */
CNode *CReplaceNode(CNode *oldNode, CNode *newNode)
{
    return xmlReplaceNode(oldNode, newNode);
}

/**
 * CFindNode ()
 * Get a child node with name 'name'. The whole subtree is searched for
 * the node and not only the direct children as with the getNode function.
 */
CNode *CFindNode(CNode *n, const CString &name)
{
    CNode *node;

    if (n == NULL)
        return NULL;

    // Try to get node at this level
    node = CGetChildNode(n, name);

    // End of recursion
    if (node != NULL)
        return node;

    // Recursion - search the children
    for (CNode *t = n->children; t != NULL && node == NULL; t = t->next)
    {
        node = CFindNode(t, name);
    }

    return node;
}

/**
 * CNextNode ()
 * Return pointer to next node on same level. If name is not NULL, next
 * node must have name 'name'.
 */
CNode *CNextNode(const CNode *n, const CString &name)
{
    CNode *t;

    for (t = n->next; t != NULL; t = t->next)
    {
        if (name.empty() || CIsNode(t, name))
            return t;
    }

    return NULL;
}

/**
 * CPreviousNode ()
 * Return pointer to previous node on same level. If name is not NULL, previous
 * node must have name 'name'.
 */
CNode *CPreviousNode(const CNode *n, const CString &name)
{
    CNode *t;

    for (t = n->prev; t != NULL; t = t->prev)
    {
        if (name.empty() || CIsNode(t, name))
            return t;
    }

    return NULL;
}

/**
 * CGetAttribute ()
 * Get the value of an attribute.
 */
CString CGetAttribute(CNode *n, const CString &name)
{
    if (CHasAttribute(n, name))
    {
        xmlChar *prop = xmlGetProp(n, (const xmlChar *)name.c_str());
        CString attr = CString((const char *)prop);
        xmlFree(prop);
        return attr;
    }
    else
    {
        std::cerr << CIsNode(n) << " " << name << std::endl;
        throw CException("(CGetAttribute) Node does not have requested attribute.");
    }

    return CString("");
}

/**
 * CHasAttribute ()
 * Check that attribute is present.
 */
bool CHasAttribute(CNode *n, const CString &name)
{
    xmlAttr *attr;

    // Find the attribute
    attr = xmlHasProp(n, (const xmlChar *) name.c_str());

    // Check attribute
    if (attr == NULL)
        return false;

    // Attribute found
    return true;
}

/**
 * CAddAttribute ()
 * Add an attribute to the node.
 */
void CAddAttribute(CNode *n, const CString &name, const CString &value)
{
    // Check that attribute is already present
    if (CHasAttribute(n, name))
    {
        // Update existing attribute
        xmlSetProp(n, (const xmlChar *) name.c_str(), (const xmlChar *)value.c_str());
    }
    else
    {
        // Create new attribute
        xmlNewProp(n, (const xmlChar *) name.c_str(), (const xmlChar *) value.c_str());
    }
}

/**
 * CSetAttribute ()
 * Set or reset an attribute of the node.
 */
void CSetAttribute(CNode *n, const CString &name, const CString &value)
{
    xmlSetProp(n, (const xmlChar *) name.c_str(), (const xmlChar *) value.c_str());
}

/**
 * CRemoveAttribute ()
 * Remove attribute from node.
 */
void CRemoveAttribute(CNode *n, const CString &name)
{
    xmlAttr *prop;

    // Find the attribute
    prop = xmlHasProp(n, (const xmlChar *) name.c_str());

    if (prop == NULL)
        return;

    // Remove the attribute
    xmlRemoveProp(prop);
}

/**
 * CSetContent ()
 * Set content of node.
 */
void CSetContent(CNode *n, const CString &cont)
{
    xmlNodeSetContent(n, (const xmlChar *) cont.c_str());
}


/**
 * CGetNumberOfChildNodes ()
 * Return the number of child nodes with name 'name'.
 */
CId CGetNumberOfChildNodes(CNode *n, const CString &name)
{
    CId NumberOfChildNodes = 0;

    if (n != NULL)
    {
        for (CNode *t = n->children; t != NULL; t = t->next)
        {
            if (name.empty() || CIsNode(t, name))
            {
                NumberOfChildNodes++;
            }
        }
    }

    return NumberOfChildNodes;
}

void releaseDoc(CDoc *doc)
{
    xmlFreeDoc(doc);
}

/**
 * Create a procesing instruction.
 */
void CAddProcessingInstruction(CDoc *doc, const CString &pi, const CString &piArgs)
{
    xmlNodePtr newPI = xmlNewDocPI(doc, (xmlChar *)pi.c_str(), (xmlChar *)piArgs.c_str());
    xmlNodePtr rootNode = xmlDocGetRootElement(doc);
    xmlAddPrevSibling(rootNode, newPI);
}

/**
 * CSetRootNode ()
 * Set the document root node
 */
void CSetRootNode(CDoc *doc, CNode *rootNode)
{
    xmlDocSetRootElement(doc, rootNode);
}


/**
 * xmlCleanup()
 * call at the end to release xml related resources.
 */
void xmlCleanup()
{
    xmlCleanupParser();
}
