/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   graph.h
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
 * $Id: graph.h,v 1.1.1.1.2.1 2010-04-24 23:52:43 mgeilen Exp $
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

#ifndef SDF_BASE_UNTIMED_GRAPH_H_INCLUDED
#define SDF_BASE_UNTIMED_GRAPH_H_INCLUDED

#include "channel.h"
namespace SDF
{


    /**
     * SDFGraph
     * Container for SDF graph.
     */
    class SDFGraph : public SDFcomponent
    {
        public:

            // Constructor
            explicit SDFGraph(SDFcomponent &c);
            SDFGraph();

            // Destructor
            ~SDFGraph() override;

            // Construct
            virtual SDFGraph *create(SDFcomponent &c) const;
            virtual SDFGraph *createCopy(SDFcomponent &c) const;
            virtual SDFGraph *clone(SDFcomponent &c) const;
            void construct(const CNodePtr sdfNode);

            // Type
            CString getType() const
            {
                return type;
            };
            void setType(const CString &t)
            {
                type = t;
            };

            // Actors
            SDFactor *getActor(const CId id);
            SDFactor *getActor(const CString &name);
            SDFactors &getActors()
            {
                return actors;
            };
            uint nrActors() const
            {
                return (uint) actors.size();
            };
            SDFactorsIter actorsBegin()
            {
                return actors.begin();
            };
            SDFactorsIter actorsEnd()
            {
                return actors.end();
            };
            SDFactorsCIter actorsBegin() const
            {
                return actors.begin();
            };
            SDFactorsCIter actorsEnd() const
            {
                return actors.end();
            };
            void addActor(SDFactor *a);
            void removeActor(const CString &name);
            virtual SDFactor *createActor();
            virtual SDFactor *createActor(SDFcomponent &c);

            // Channels
            SDFchannel *getChannel(const CId id);
            SDFchannel *getChannel(const CString &name);
            uint nrChannels() const
            {
                return (uint) channels.size();
            };
            SDFchannelsIter channelsBegin()
            {
                return channels.begin();
            };
            SDFchannelsIter channelsEnd()
            {
                return channels.end();
            };
            SDFchannelsCIter channelsBegin() const
            {
                return channels.begin();
            };
            SDFchannelsCIter channelsEnd() const
            {
                return channels.end();
            };
            void addChannel(SDFchannel *c);
            void removeChannel(const CString &name);
            virtual SDFchannel *createChannel(SDFcomponent &c);
            SDFchannel *createChannel(SDFactor *src, SDFrate rateSrc, SDFactor *dst,
                                      SDFrate rateDst, uint initialTokens);

            // Print
            ostream &print(ostream &out);
            friend ostream &operator<<(ostream &out, SDFGraph &g)
            {
                return g.print(out);
            };

        private:
            // Graph type
            CString type;

            // Actors and channels
            SDFactors   actors;
            SDFchannels channels;

    };

    typedef list<SDFGraph *>            SDFgraphs;
    typedef SDFgraphs::iterator         SDFgraphsIter;
    typedef SDFgraphs::const_iterator   SDFgraphsCIter;

}//namespace SDF
#endif
