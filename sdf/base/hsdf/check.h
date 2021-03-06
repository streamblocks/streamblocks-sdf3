/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   check.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 22, 2005
 *
 *  Function        :   Check that SDF graph is a HSDF graph
 *
 *  History         :
 *      22-07-05    :   Initial version.
 *
 * $Id: check.h,v 1.1.1.1 2007-10-02 10:59:46 sander Exp $
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

#ifndef SDF_BASE_HSDF_CHECK_H_INCLUDED
#define SDF_BASE_HSDF_CHECK_H_INCLUDED

#include "../untimed/graph.h"
namespace SDF
{


    /**
     * isHSDFgraph ()
     * The function checks wether a SDF graph is a HSDF graph.
     */
    bool isHSDFgraph(SDFGraph *g);

}//namespace SDF
#endif
