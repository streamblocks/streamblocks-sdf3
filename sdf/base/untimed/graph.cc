/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   graph.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 13, 2005
 *
 *  Function        :   SDF graph
 *
 *  History         :
 *      13-07-05    :   Initial version.
 *
 * $Id: graph.cc,v 1.1.1.1.2.1 2010-05-10 22:25:02 mgeilen Exp $
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

#include "graph.h"
namespace SDF
{


    /**
     * SDFGraph ()
     * Constructor.
     */
    SDFGraph::SDFGraph(SDFcomponent &c)
        :
        SDFcomponent(c)
    {
    }

    /**
     * SDFGraph ()
     * Constructor.
     */
    SDFGraph::SDFGraph()
        :
        SDFcomponent()
    {
    }

    /**
     * SDFGraph ()
     * Destructor.
     */
    SDFGraph::~SDFGraph()
    {
        // Actors
        for (auto a : actors)
        {
            delete a;
        }

        // Channels
        for (auto c : channels)
        {
            delete c;
        }
    }

    /**
     * create ()
     * The function returns a pointer to a newly allocated SDF graph object.
     */
    SDFGraph *SDFGraph::create(SDFcomponent &c) const
    {
        return new SDFGraph(c);
    }

    /**
     * clone ()
     * The function returns a pointer to a newly allocated SDF graph object.
     * All properties, actors and channels of the graph are cloned.
     */
    SDFGraph *SDFGraph::clone(SDFcomponent &c) const
    {
        auto *g = new SDFGraph(c);

        // Properties
        g->setName(getName());
        g->setType(getType());

        // Actors
        for (auto actor : actors)
        {
            SDFcomponent component = SDFcomponent(g, g->nrActors());
            SDFactor *a = actor->clone(component);
            g->addActor(a);
        }

        // Channels
        for (auto channel : channels)
        {
            SDFcomponent component = SDFcomponent(g, g->nrChannels());
            SDFchannel *ch = channel->clone(component);
            g->addChannel(ch);
        }

        return g;
    }

    /**
     * createCopy ()
     * The function returns a pointer to a newly allocated SDF graph object.
     * All properties of the graph are copied.
     */
    SDFGraph *SDFGraph::createCopy(SDFcomponent &c) const
    {
        auto *g = new SDFGraph(c);

        // Properties
        g->setName(getName());
        g->setType(getType());

        return g;
    }

    /**
     * construct ()
     * The function initializes all actor properties based on the XML data.
     */
    void SDFGraph::construct(const CNodePtr sdfNode)
    {
        SDFcomponent component;

        // Name
        if (!CHasAttribute(sdfNode, "name"))
            throw CException("Invalid SDF graph, missing graph name.");
        setName(CGetAttribute(sdfNode, "name"));

        // Type
        if (!CHasAttribute(sdfNode, "type"))
            throw CException("Invalid SDF graph, missing graph type.");
        setType(CGetAttribute(sdfNode, "type"));

        // Construct all actors
        for (CNodePtr actorNode = CGetChildNode(sdfNode, "actor");
             actorNode != nullptr; actorNode = CNextNode(actorNode, "actor"))
        {
            // Construct actor
            component = SDFcomponent(this, nrActors());
            SDFactor *a = createActor(component);
            a->construct(actorNode);

            // Construct all ports
            for (CNodePtr portNode = CGetChildNode(actorNode, "port");
                 portNode != nullptr; portNode = CNextNode(portNode, "port"))
            {
                // Construct port
                component = SDFcomponent(a, a->nrPorts());
                auto *p = new SDFport(component);
                p->construct(portNode);

                // Add port to actor
                a->addPort(p);
            }
        }

        // Construct all channels
        for (CNodePtr channelNode = CGetChildNode(sdfNode, "channel");
             channelNode != nullptr;
             channelNode = CNextNode(channelNode, "channel"))
        {
            // Construct channel
            component = SDFcomponent(this, nrChannels());
            SDFchannel *c = createChannel(component);
            c->construct(channelNode);
        }
    }

    /**
     * getActor ()
     * The function returns a reference to an actor with the given id.
     */
    SDFactor *SDFGraph::getActor(const CId id)
    {
        for (auto a : actors)
        {
            if (a->getId() == id)
                return a;
        }

        throw CException("Graph '" + getName() + "' has no actor with id '"
                         + CString(id) + "'.");
    }

    /**
     * getActor ()
     * The function returns a reference to an actor with the given name.
     */
    SDFactor *SDFGraph::getActor(const CString &name)
    {
        for (auto a : actors)
        {
            if (a->getName() == name)
                return a;
        }

        return nullptr;
    }

    /**
     * addActor ()
     * Add an actor to a graph.
     */
    void SDFGraph::addActor(SDFactor *a)
    {
        actors.push_back(a);
    }

    /**
     * removeActor ()
     * Remove an actor from a graph.
     */
    void SDFGraph::removeActor(const CString &name)
    {
        for (auto iter = actors.begin(); iter != actors.end(); iter++)
        {
            SDFactor *a = *iter;

            if (a->getName() == name)
            {
                actors.erase(iter);
                return;
            }
        }

        throw CException("Graph '" + getName() + "' has no actor '" + name + "'.");
    }

    /**
     * createActor ()
     * Create a new actor on the graph.
     */
    SDFactor *SDFGraph::createActor()
    {
        SDFcomponent c = SDFcomponent(this, nrActors());
        auto *a = new SDFactor(c);
        a->setName(CString("_a") + CString(nrActors() + 1));
        addActor(a);

        return a;
    }

    /**
     * createActor ()
     * Create a new actor on the graph.
     */
    SDFactor *SDFGraph::createActor(SDFcomponent &c)
    {
        auto *a = new SDFactor(c);
        addActor(a);

        return a;
    }

    /**
     * getChannel ()
     * The function returns a reference to a channel with the given id.
     */
    SDFchannel *SDFGraph::getChannel(const CId id)
    {
        for (auto c : channels)
        {
            if (c->getId() == id)
                return c;
        }

        throw CException("Graph '" + getName()
                         + "' has no channel with id '" + CString(id) + "'.");
    }

    /**
     * getChannel ()
     * The function returns a reference to a channel with the given name.
     */
    SDFchannel *SDFGraph::getChannel(const CString &name)
    {
        for (auto c : channels)
        {
            if (c->getName() == name)
                return c;
        }

        return nullptr;
    }

    /**
     * addChannel ()
     * Add a channel to a graph.
     */
    void SDFGraph::addChannel(SDFchannel *c)
    {
        channels.push_back(c);
    }

    /**
     * removeChannel ()
     * Remove a channel from a graph.
     */
    void SDFGraph::removeChannel(const CString &name)
    {
        for (auto iter = channels.begin();
             iter != channels.end(); iter++)
        {
            SDFchannel *c = *iter;

            if (c->getName() == name)
            {
                delete c;
                channels.erase(iter);
                return;
            }
        }

        throw CException("Graph '" + getName()
                         + "' has no channel '" + name + "'.");
    }

    /**
     * createChannel ()
     * Create a new channel on the graph.
     */
    SDFchannel *SDFGraph::createChannel(SDFcomponent &c)
    {
        auto *ch = new SDFchannel(c);
        addChannel(ch);

        return ch;
    }

    /**
     * createChannel ()
     * The function creates a channel between the source and destination actor.
     * Ports with the supplied rates are added to these actors.
     */
    SDFchannel *SDFGraph::createChannel(SDFactor *src, SDFrate rateSrc,
                                        SDFactor *dst, SDFrate rateDst, uint initialTokens)
    {
        // Create new channel
        SDFcomponent c = SDFcomponent(this, nrChannels());
        SDFchannel *ch = createChannel(c);
        ch->setName(CString("_ch") + CString(nrChannels()));

        // Create ports on the actors
        SDFport *srcP = src->createPort(SDFport::Out, rateSrc);
        srcP->setName(CString("_p") + CString(src->nrPorts()));
        SDFport *dstP = dst->createPort(SDFport::In, rateDst);
        dstP->setName(CString("_p") + CString(dst->nrPorts()));

        // Connect channel
        ch->connectSrc(srcP);
        ch->connectDst(dstP);

        // Initial tokens
        ch->setInitialTokens(initialTokens);

        return ch;
    }

    /**
     * print ()
     * Print the graph to the supplied output stream.
     */
    ostream &SDFGraph::print(ostream &out)
    {
        out << "Graph (" << getName() << ")" << endl;
        out << "id:        " << getId() << endl;
        out << "type:      " << getType() << endl;
        out << endl;

        for (auto a : actors)
        {
            a->print(out);
        }

        for (auto c : channels)
        {
            c->print(out);
        }

        out << endl;

        return out;
    }
}//namespace SDF
