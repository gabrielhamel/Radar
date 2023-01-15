#include "radar/entities/hitbox.h"

sfCircleShape *render_circle_create(sfVector2f initial_pos, float radius)
{
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape_setPosition(circle, initial_pos);
    sfCircleShape_setOutlineColor(circle, sfBlue);
    sfCircleShape_setFillColor(circle, sfTransparent);
    sfCircleShape_setOutlineThickness(circle, 2);
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setPointCount(circle, 40);
    sfCircleShape_setOrigin(circle, (sfVector2f){
        radius,
        radius
    });
    return circle;
}

sfRectangleShape *render_rect_create(sfVector2f initial_pos, bool enabled)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfRectangleShape_setPosition(rect, initial_pos);
    sfRectangleShape_setOutlineColor(rect, sfGreen);
    sfRectangleShape_setFillColor(rect, sfTransparent);
    sfRectangleShape_setOutlineThickness(rect, enabled ? 2 : 0);
    sfRectangleShape_setSize(rect, (sfVector2f){
        20,
        20
    });
    sfRectangleShape_setOrigin(rect, (sfVector2f){
        10,
        10
    });
    return rect;
}

sfConvexShape *render_custom_create(sfVector2f initial_pos, sfVector2f *points, size_t count)
{
    sfConvexShape *shape = sfConvexShape_create();
    sfConvexShape_setPointCount(shape, count);
    for (size_t idx = 0; idx < count; idx++) {
        sfConvexShape_setPoint(shape, idx, points[idx]);
    }
    sfTexture *texture = sfTexture_createFromFile("assets/storm.png", NULL);
    sfTexture_setRepeated(texture, sfTrue);
    sfConvexShape_setTexture(shape, texture, sfTrue);
    sfConvexShape_setTextureRect(shape, (sfIntRect){0, 0, 4800, 3200});
    sfConvexShape_setPosition(shape, initial_pos);
    sfConvexShape_setOutlineColor(shape, sfRed);
    sfConvexShape_setOutlineThickness(shape, 2);
    return shape;
}