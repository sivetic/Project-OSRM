/*
 open source routing machine
 Copyright (C) Dennis Luxen, others 2010

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU AFFERO General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 or see http://www.gnu.org/licenses/agpl.txt.
 */

/*
 * This class constructs the edge base representation of a graph from a given node based edge list
 */

#ifndef EDGEBASEDGRAPHFACTORY_H_
#define EDGEBASEDGRAPHFACTORY_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "../typedefs.h"
#include "../DataStructures/DynamicGraph.h"
#include "../DataStructures/ExtractorStructs.h"
#include "../DataStructures/ImportEdge.h"
#include "../DataStructures/Percent.h"
#include "../DataStructures/TurnInstructions.h"

class EdgeBasedGraphFactory {
private:
    struct _NodeBasedEdgeData {
        int distance;
        unsigned edgeBasedNodeID;
        unsigned nameID;
        bool shortcut:1;
        bool forward:1;
        bool backward:1;
        bool roundabout:1;
        short type;
    } data;

    struct _EdgeBasedEdgeData {
        int distance;
        unsigned via;
        unsigned nameID;
        bool forward;
        bool backward;
        short turnInstruction;
    };

    typedef DynamicGraph< _NodeBasedEdgeData > _NodeBasedDynamicGraph;
    typedef _NodeBasedDynamicGraph::InputEdge _NodeBasedEdge;

public:
    struct EdgeBasedNode {
        bool operator<(const EdgeBasedNode & other) const {
            return other.id < id;
        }
        bool operator==(const EdgeBasedNode & other) const {
            return id == other.id;
        }
        int lat1;
        int lat2;
        int lon1;
        int lon2;
        NodeID id;
        NodeID nameID;
        unsigned weight;
    };

private:
    boost::shared_ptr<_NodeBasedDynamicGraph> _nodeBasedGraph;

    std::vector<_Restriction> & inputRestrictions;
    std::vector<NodeInfo> & inputNodeInfoList;

    std::vector<EdgeBasedEdge> edgeBasedEdges;
    std::vector<EdgeBasedNode> edgeBasedNodes;

    template<class CoordinateT>
    double GetAngleBetweenTwoEdges(const CoordinateT& A, const CoordinateT& C, const CoordinateT& B) const;
public:
    template< class InputEdgeT >
    explicit EdgeBasedGraphFactory(int nodes, std::vector<InputEdgeT> & inputEdges, std::vector<_Restriction> & inputRestrictions, std::vector<NodeInfo> & nI);
    virtual ~EdgeBasedGraphFactory();

    void Run();
    template< class ImportEdgeT >
    void GetEdgeBasedEdges( std::vector< ImportEdgeT >& edges );
    void GetEdgeBasedNodes( std::vector< EdgeBasedNode> & nodes);
    short AnalyzeTurn(const NodeID u, const NodeID v, const NodeID w) const;
    unsigned GetNumberOfNodes() const;
};

#endif /* EDGEBASEDGRAPHFACTORY_H_ */
