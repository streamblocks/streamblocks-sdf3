/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   actor.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 13, 2005
 *
 *  Function        :   SDF actor
 *
 *  History         :
 *      13-07-05    :   Initial version.
 *
 * $Id: actor.h,v 1.1.1.1.2.2 2010-04-24 23:52:43 mgeilen Exp $
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

#ifndef SDF_BASE_UNTIMED_ACTOR_H_INCLUDED
#define SDF_BASE_UNTIMED_ACTOR_H_INCLUDED

#include "port.h"
#include <list>
namespace SDF
{


    /**
     * SDFactor
     * Actor in SDF graph
     */
    class SDFactor : public SDFcomponent
    {
        public:

            // Constructor
            explicit SDFactor(SDFcomponent &c);

            // Desctructor
            ~SDFactor() override;

            // Construct
            virtual SDFactor *create(SDFcomponent &c) const;
            virtual SDFactor *createCopy(SDFcomponent &c) const;
            virtual SDFactor *clone(SDFcomponent &c) const;
            void construct(const CNodePtr actorNode);

            // Type
            CString getType() const
            {
                return type;
            };
            void setType(const CString &t)
            {
                type = t;
            };

            // Ports
            SDFport *getPort(const CId id);
            SDFport *getPort(const CString &name);
            uint nrPorts() const
            {
                return (uint) ports.size();
            };
            SDFportsIter portsBegin()
            {
                return ports.begin();
            };
            SDFportsIter portsEnd()
            {
                return ports.end();
            };
            SDFportsCIter portsBegin() const
            {
                return ports.begin();
            };
            SDFportsCIter portsEnd() const
            {
                return ports.end();
            };
            void addPort(SDFport *p);
            void removePort(const CString &name);
            virtual SDFport *createPort(SDFcomponent &c);
            SDFport *createPort(const SDFport::SDFportType type, const SDFrate rate);

            // Properties
            bool isConnected() const;

            // Graph
            SDFGraph *getGraph() const
            {
                return (SDFGraph *)getParent();
            };

            // Print
            ostream &print(ostream &out);
            friend ostream &operator<<(ostream &out, SDFactor &a)
            {
                return a.print(out);
            };

        private:
            // Type
            CString type;

            // Ports
            SDFports ports;
    };

    typedef std::list<SDFactor *>       SDFactors;
    typedef SDFactors::iterator         SDFactorsIter;
    typedef SDFactors::const_iterator   SDFactorsCIter;

}//namespace SDF
#endif
