/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   hapi.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   August 1, 2005
 *
 *  Function        :   Output SDF graph in HAPI format
 *
 *  History         :
 *      01-08-05    :   Initial version.
 *
 * $Id: hapi.cc,v 1.1.1.1 2007-10-02 10:59:46 sander Exp $
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

#include "hapi.h"
namespace SDF
{


    /**
     * sdfToHapiComment ()
     * The function outputs a comment string with the tool name.
     */
    void sdfToHapiComment(ostream &out)
    {
        out << "/**" << endl;
        out << " * This file is automatically generated with smart." << endl;
        out << " *" << endl;
        out << " * http://www.es.ele.tue.nl/promes/" << endl;
        out << " */" << endl;
    }

    /**
     * hapiActorDelcaration ()
     * Output an SDF actor declaration to the output stream
     */
    void hapiActorDeclaration(ostream &out, TimedSDFactor *a)
    {
        // Declaration
        out << "class " << a->getType() << " : public Process" << endl;
        out << "{" << endl;
        out << "public:" << endl;

        // Constructor
        out << "\t// Constructor" << endl;
        out << "\t" << a->getType() << "(" << endl;
        out << "\t\tconst class Id &n";

        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;
            TimedSDFchannel *c = (TimedSDFchannel *)p->getChannel();

            out << "," << endl;
            out << "\t\t";

            if (p->getType() == SDFport::In)
                out << "In";
            else
                out << "Out";

            out << " < " << c->getTokenType() << " > &" << p->getName() << "_F";
        }
        out << endl;
        out << "\t);" << endl;
        out << endl;

        // Destructor
        //out << "\t// Destructor" << endl;
        //out << "\t~" << a.getType() << "();" << endl;
        //out << endl;

        // Type
        out << "\t// type member function" << endl;
        out << "\tconst char *type() const" << endl;
        out << "\t\t{ return \"" << a->getType() << "\"; };" << endl;
        out << endl;

        // Main
        out << "\t// main member function" << endl;
        out << "\tvoid main();" << endl;
        out << endl;

        out << "private:" << endl;

        // Ports
        out << "\t// Ports" << endl;
        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;
            TimedSDFchannel *c = (TimedSDFchannel *)p->getChannel();

            if (p->getType() == SDFport::In)
                out << "\tInPort";
            else
                out << "\tOutPort";

            out << " < " << c->getTokenType() << " > ";
            out << p->getName() << ";" << endl;
        }

        // End of declaration
        out << "};" << endl;
    }

    /**
     * hapiActorConstructor ()
     * Output an SDF actor class to the output stream
     */
    void hapiActorConstructor(ostream &out, TimedSDFactor *a)
    {

        out << a->getType() << "::" << a->getType() << "(" << endl;
        out << "\tconst class Id &n";

        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;
            TimedSDFchannel *c = (TimedSDFchannel *)p->getChannel();

            out << "," << endl;
            out << "\t";

            if (p->getType() == SDFport::In)
                out << "In";
            else
                out << "Out";

            out << " < " << c->getTokenType() << " > &" << p->getName() << "_F";
        }
        out << ")" << endl;

        out << "\t\t:" << endl;
        out << "\tProcess(n)";

        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;

            out << "," << endl;
            out << "\t";

            out << p->getName() << "(id(\"" << p->getName() << "\"), ";
            out << p->getName() << "_F)";
        }
        out << endl;
        out << "{" << endl;
        out << "}" << endl;
        out << endl;
    }

    /**
     * hapiActorMain ()
     * Output an SDF actors main function to the output stream
     */
    void hapiActorMain(ostream &out, TimedSDFactor *a)
    {
        out << "void " << a->getType() << "::main()" << endl;
        out << "{" << endl;

        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;
            TimedSDFchannel *c = (TimedSDFchannel *)p->getChannel();

            out << "\t" << c->getTokenType() << " d_" << p->getName();
            out << "[" << p->getRate() << "];" << endl;
        }
        out << endl;

        out << "\twhile (true)" << endl;
        out << "\t{" << endl;

        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;

            if (p->getType() == SDFport::Out)
                continue;

            out << "\t\tread(" << p->getName() << ", d_" << p->getName();
            out << ", " << p->getRate() << ");" << endl;
        }

        out << endl;

        for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
        {
            SDFport *p = *iter;

            if (p->getType() == SDFport::In)
                continue;

            out << "\t\twrite(" << p->getName() << ", d_" << p->getName();
            out << ", " << p->getRate() << ");" << endl;
        }

        out << "\t}" << endl;

        out << "}" << endl;
        out << endl;
    }

    /**
     * hapiActorDelcarationH ()
     * Output an SDF actor declaration header file to the output stream
     */
    void hapiActorDeclarationH(ostream &out, TimedSDFactor *a)
    {
        sdfToHapiComment(out);

        out << "#ifndef " << a->getType().toUpper() << "_H" << endl;
        out << "#define " << a->getType().toUpper() << "_H" << endl;
        out << endl;
        out << "#include \"process.h\"" << endl;
        out << "#include \"port.h\"" << endl;
        out << endl;
        out << "#include \"types.h\"" << endl;
        out << endl;

        hapiActorDeclaration(out, a);

        out << endl;
        out << "#endif" << endl;
    }

    /**
     * hapiActorDelcarationCC ()
     * Output an SDF actor defenition to the output stream
     */
    void hapiActorDeclarationCC(ostream &out, TimedSDFactor *a)
    {
        sdfToHapiComment(out);

        out << "#include \"" << a->getType().toLower() << ".h\"" << endl;
        out << endl;

        hapiActorConstructor(out, a);
        hapiActorMain(out, a);
    }

    /**
     * hapiNetworkDelcaration ()
     * Output an SDF graph declaration to the output stream
     */
    void hapiNetworkDeclaration(ostream &out, TimedSDFgraph *g)
    {
        // Declaration
        out << "class " << g->getType() << " : public ProcessNetwork" << endl;
        out << "{" << endl;
        out << "public:" << endl;

        // Constructor
        out << "\t// Constructor" << endl;
        out << "\t" << g->getType() << "(const class Id &n);" << endl;
        out << endl;

        // Destructor
        //out << "\t// Destructor" << endl;
        //out << "\t~" << g.getType() << "();" << endl;
        //out << endl;

        // Type
        out << "\t// type member function" << endl;
        out << "\tconst char *type() const" << endl;
        out << "\t\t{ return \"" << g->getType() << "\"; };" << endl;
        out << endl;

        out << "private:" << endl;

        // Fifos
        out << "\t// Fifos" << endl;
        for (SDFchannelsIter iter = g->channelsBegin();
             iter != g->channelsEnd(); iter++)
        {
            TimedSDFchannel *c = (TimedSDFchannel *)*iter;

            out << "\tFifo < " << c->getTokenType() << " > ";
            out << c->getName() << ";" << endl;
        }
        out << endl;

        // Processes
        out << "\t// Processes" << endl;
        for (SDFactorsIter iter = g->actorsBegin();
             iter != g->actorsEnd(); iter++)
        {
            SDFactor *a = *iter;

            out << "\t" << a->getType() << " " << a->getName() << ";" << endl;
        }

        // End of declaration
        out << "};" << endl;
    }

    /**
     * hapiNetworkConstructor ()
     * Output an SDF graph constructor to the output stream
     */
    void hapiNetworkConstructor(ostream &out, SDFGraph *g)
    {
        out << g->getType() << "::" << g->getType() << "(const class Id &n) :";
        out << endl;
        out << "\tProcessNetwork(n)";

        for (SDFchannelsIter iter = g->channelsBegin();
             iter != g->channelsEnd(); iter++)
        {
            SDFchannel *c = *iter;

            out << "," << endl;

            out << "\t" << c->getName() << "(id(\"" << c->getName() << "\"))";
        }

        for (SDFactorsIter iter = g->actorsBegin();
             iter != g->actorsEnd(); iter++)
        {
            SDFactor *a = *iter;

            out << "," << endl;

            out << "\t" << a->getName() << "(" << endl;
            out << "\t\tid(\"" << a->getName() << "\")";

            for (SDFportsIter iter = a->portsBegin(); iter != a->portsEnd(); iter++)
            {
                SDFport *p = *iter;
                SDFchannel *c = p->getChannel();

                out << "," << endl;
                out << "\t\t" << c->getName();
            }

            out << endl << "\t)";
        }
        out << endl;

        out << "{" << endl;
        out << "}" << endl;
    }

    /**
     * hapiNetworkDelcarationH ()
     * Output an SDF graph header to the output stream
     */
    void hapiNetworkDeclarationH(ostream &out, TimedSDFgraph *g)
    {
        sdfToHapiComment(out);

        out << "#ifndef " << g->getType().toUpper() << "_H" << endl;
        out << "#define " << g->getType().toUpper() << "_H" << endl;
        out << endl;
        out << "#include \"network.h\"" << endl;
        out << "#include \"fifo.h\"" << endl;
        out << endl;
        out << "#include \"types.h\"" << endl;
        out << endl;

        for (SDFactorsIter iter = g->actorsBegin();
             iter != g->actorsEnd(); iter++)
        {
            SDFactor *a = *iter;

            out << "#include \"" << a->getType().toLower() << ".h\"" << endl;
        }
        out << endl;

        hapiNetworkDeclaration(out, g);

        out << endl;
        out << "#endif" << endl;
    }

    /**
     * hapiNetworkDeclarationCC ()
     * Output an SDF graph declaration to the output stream
     */
    void hapiNetworkDeclarationCC(ostream &out, TimedSDFgraph *g)
    {
        sdfToHapiComment(out);

        out << "#include \"" << g->getType().toLower() << ".h\"" << endl;
        out << endl;

        hapiNetworkConstructor(out, g);
    }

    /**
     * hapiMain ()
     * The function creates a main function to simulate a hapi network.
     */
    void hapiMain(ostream &out, TimedSDFgraph *g)
    {
        out << "int main(int argc, char **argv)" << endl;
        out << "{" << endl;
        out << "\tRTE rte;" << endl;
        out << endl;
        out << "\t" << g->getType() << " ";
        out << g->getName() << "(id(\"" << g->getName() << "\"));" << endl;
        out << endl;
        out << "\tstd::ofstream fdot(\"" << g->getName() << ".dot\");" << endl;
        out << "\tprintDotty(" << g->getName() << ", fdot);" << endl;
        out << endl;
        out << "\trte.start(" << g->getName() << ");" << endl;
        out << endl;
        out << "\treturn 0;" << endl;
        out << "}" << endl;
    }

    /**
     * hapiMainCC ()
     * The function creates a main function to simulate a hapi network.
     */
    void hapiMainCC(ostream &out, TimedSDFgraph *g)
    {
        sdfToHapiComment(out);

        out << "#include <fstream>" << endl;
        out << "#include \"yapi.h\"" << endl;
        out << "#include \"" << g->getType().toLower() << ".h\"" << endl;
        out << endl;

        hapiMain(out, g);
    }

    /**
     * createHapiActor ()
     * The function creates files with the names actor type '.cc' and '.h' with
     * the declaration of an actor of the given type.
     */
    void createHapiActor(TimedSDFactor *a)
    {
        ofstream file;

        // Open output file
        file.open(a->getType().toLower() + ".h");
        if (!file.is_open())
            throw CException("Failed opening file.");

        // Create header file
        hapiActorDeclarationH(file, a);

        // Close output file
        file.close();

        // Open output file
        file.open(a->getType().toLower() + ".cc");
        if (!file.is_open())
            throw CException("Failed opening file.");

        // Create header file
        hapiActorDeclarationCC(file, a);

        // Close output file
        file.close();
    }

    /**
     * createHapiNetwork ()
     * The function creates a SDF graph in the files '<graph type>.cc' and '<>.h'.
     */
    void createHapiNetwork(TimedSDFgraph *g)
    {
        ofstream file;

        // Open output file
        file.open(g->getName().toLower() + ".h");
        if (!file.is_open())
            throw CException("Failed opening file.");

        // Create header file
        hapiNetworkDeclarationH(file, g);

        // Close output file
        file.close();

        // Open output file
        file.open(g->getName().toLower() + ".cc");
        if (!file.is_open())
            throw CException("Failed opening file.");

        // Create header file
        hapiNetworkDeclarationCC(file, g);

        // Close output file
        file.close();
    }

    /**
     * createHapiMain ()
     * The function creates a file with the main function to simulate
     * a hapi network.
     */
    void createHapiMain(TimedSDFgraph *g)
    {
        ofstream file;

        // Open output file
        file.open("main.cc");
        if (!file.is_open())
            throw CException("Failed opening file.");

        // Create header file
        hapiMainCC(file, g);

        // Close output file
        file.close();
    }

    /**
     * outputSDFasHAPI ()
     * The function translates an SDF graph to an HAPI network.
     */
    void outputSDFasHAPI(TimedSDFgraph *g)
    {
        // Create actor for each type
        for (SDFactorsIter iter = g->actorsBegin();
             iter != g->actorsEnd(); iter++)
        {
            TimedSDFactor *a = (TimedSDFactor *)*iter;

            createHapiActor(a);
        }

        // Create network
        createHapiNetwork(g);

        // Create a main function
        createHapiMain(g);
    }
}//namespace SDF
