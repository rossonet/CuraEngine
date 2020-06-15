//Copyright (c) 2020 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.


#ifndef UTILS_EXTRUSION_SEGMENT_H
#define UTILS_EXTRUSION_SEGMENT_H

#include <utility>

#include "IntPoint.h"
#include "polygon.h"
#include "polygonUtils.h"
#include "ExtrusionJunction.h"

namespace arachne
{
    using namespace cura;

/*!
 * Represents a single line segment as part of an extrusion path.
 *
 * This supports varying line width, since the two junctions this is composed
 * out of can have different widths.
 */
class ExtrusionSegment
{
    static constexpr float a_step = 15 / 180.0 * M_PI;
public:
    ExtrusionJunction from;
    ExtrusionJunction to;

    bool is_odd; //!< Whether this is a polyline segment rather than a polygonal segment
    bool is_reduced; //!< Whether to remove the circle from the to-location because it will be included in the next extrusion move

    ExtrusionSegment(ExtrusionJunction from, ExtrusionJunction to, bool is_odd, bool is_reduced)
    : from(from)
    , to(to)
    , is_odd(is_odd)
    , is_reduced(is_reduced)
    {}

    /*!
     * Converts this segment to an outline of the area that the segment covers.
     * \return The area that would be covered by this extrusion segment.
     */
    Polygons toPolygons(); 

    /*!
     * Converts this segment to an outline of the area that the segment covers.
     * \param reduced Whether to remove the circle from the to-location because
     * it will be included in the next extrusion move. Overrides class field
     * \ref is_reduced .
     */
    Polygons toPolygons(bool reduced);

    /*!
     * Discretize a variable-line-width extrusion segment into multiple
     * constant-line-width extrusion segments.
     *
     * The line segments will have the length of approximately the step size. If
     * this doesn't fit, the number of steps is rounded to the nearest integer,
     * and the steps may be slightly longer or shorter.
     * \param step_size The desired length of the steps. A smaller step size
     * gives better width resolution, but increases the number of segments,
     * resulting in longer processing and a larger file in the end.
     * \return A list of extrusion segments. All of these extrusion segments
     * have a constant line width.
     */
    std::vector<ExtrusionSegment> discretize(coord_t step_size);
};




} // namespace arachne
#endif // UTILS_EXTRUSION_SEGMENT_H
