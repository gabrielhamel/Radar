#include <engine/tools/maths.h>
#include <radar/systems/hitbox.h>
#include <radar/components/hitbox.h>
#include <radar/components/position.h>

static bool segment_intersect_segment(sfVector2f a1, sfVector2f a2, sfVector2f b1, sfVector2f b2)
{
    // Avoid 0 div
    if (a2.x - a1.x == 0 || b2.x - b1.x == 0) {
        return false;
    }

    float fa1 = (a2.y - a1.y) / (a2.x - a1.x);
    float fa2 = (b2.y - b1.y) / (b2.x - b1.x);
    float fb1 = a1.y - fa1 * a1.x;
    float fb2 = b1.y - fa2 * b1.x;

    // Avoid 0 div
    if (fa1 - fa2 == 0) {
        return false;
    }
    float intersect_x = (fb2 - fb1) / (fa1 - fa2);

    // Take the smallest x point
    float s1_x_min = min(a1.x, a2.x);
    float s2_x_min = min(b1.x, b2.x);
    float s_min = max(s1_x_min, s2_x_min);

    // Take the biggest x point
    float s1_x_max = max(a1.x, a2.x);
    float s2_x_max = max(b1.x, b2.x);
    float s_max = min(s1_x_max, s2_x_max);

    return intersect_x >= s_min && intersect_x <= s_max;
}

bool custom_intersect_custom(entity_t *a, entity_t *b)
{
    sfVector2f pos_a = entity_get_component_data(a, POSITION_COMPONENT_TYPE, position_component_t)->position;
    sfVector2f pos_b = entity_get_component_data(b, POSITION_COMPONENT_TYPE, position_component_t)->position;

    hitbox_component_t *a_h = entity_get_component_data(a, HITBOX_COMPONENT_TYPE, hitbox_component_t);
    hitbox_component_t *b_h = entity_get_component_data(b, HITBOX_COMPONENT_TYPE, hitbox_component_t);

    for (size_t it_a = 0; it_a < a_h->point_count - 1; it_a++) {
        for (size_t it_b = 0; it_b < b_h->point_count - 1; it_b++) {
            if (segment_intersect_segment(
                    (sfVector2f){a_h->points[it_a].x + pos_a.x, a_h->points[it_a].y + pos_a.y},
                    (sfVector2f){a_h->points[it_a + 1].x + pos_a.x, a_h->points[it_a + 1].y + pos_a.y},
                    (sfVector2f){b_h->points[it_b].x + pos_b.x, b_h->points[it_b].y + pos_b.y},
                    (sfVector2f){b_h->points[it_b + 1].x + pos_b.x, b_h->points[it_b + 1].y + pos_b.y}
            )) {
                return true;
            }
        }
    }
    // Last a segment
    for (size_t it_b = 0; it_b < b_h->point_count - 1; it_b++) {
        if (segment_intersect_segment(
                (sfVector2f){a_h->points[a_h->point_count - 1].x + pos_a.x, a_h->points[a_h->point_count - 1].y + pos_a.y},
                (sfVector2f){a_h->points[0].x + pos_a.x, a_h->points[0].y + pos_a.y},
                (sfVector2f){b_h->points[it_b].x + pos_b.x, b_h->points[it_b].y + pos_b.y},
                (sfVector2f){b_h->points[it_b + 1].x + pos_b.x, b_h->points[it_b + 1].y + pos_b.y}
        )) {
            return true;
        }
    }
    // Last b segment
    for (size_t it_a = 0; it_a < a_h->point_count - 1; it_a++) {
        if (segment_intersect_segment(
                (sfVector2f){a_h->points[it_a].x + pos_a.x, a_h->points[it_a].y + pos_a.y},
                (sfVector2f){a_h->points[it_a + 1].x + pos_a.x, a_h->points[it_a + 1].y + pos_a.y},
                (sfVector2f){b_h->points[b_h->point_count - 1].x + pos_b.x, b_h->points[b_h->point_count - 1].y + pos_b.y},
                (sfVector2f){b_h->points[0].x + pos_b.x, b_h->points[0].y + pos_b.y}
        )) {
            return true;
        }
    }
    return false;
}