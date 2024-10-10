#include "raylib.h"
#include "raymath.h"

/*
 * Draggable implementation
*/

#include "draggable.h"

draggable
create_draggable (const Vector2 position, const Vector2 size) {
    draggable new_draggable;
    const float default_area_size = 32.0f;

    new_draggable.original_position = position;
    new_draggable.actual_position = position;
    new_draggable.is_selected = false;
    new_draggable.state = DRAGGABLE_IDLE;

    // If size is zero or less, then the size of the area will be 32x32 (default)
    if (size.x <= 0 && size.y <= 0) {
        new_draggable.area = (Rectangle) { position.x, position.y, default_area_size, default_area_size };
        return new_draggable;
    }

    new_draggable.area = (Rectangle){ position.x, position.y, size.x, size.y };

    return new_draggable;
}

void
update_draggable (draggable *draggable) {
    const Rectangle mouseRec = { GetMouseX(), GetMouseY(), 1, 1 };

    switch (draggable->state) {
        case DRAGGABLE_IDLE:
            if (CheckCollisionRecs(draggable->area, mouseRec) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                draggable->is_selected = true;
                draggable->state = DRAGGABLE_DRAGGING;
            }
            break;

        case DRAGGABLE_DRAGGING:
            draggable->actual_position = GetMousePosition();

            // Center the cursor to the area
            draggable->actual_position.x -= ( draggable->area.width / 2 );
            draggable->actual_position.y -= ( draggable->area.height / 2 );

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                draggable->state = DRAGGABLE_RESETTING;
            }
            
            break;

        case DRAGGABLE_RESETTING:
            reset_draggable(draggable);
            break;

        default:
            break;
    }

    // Updates the position only if the draggable object is not in its original position.
    if (!Vector2Equals(draggable->actual_position, draggable->original_position)) {
        draggable->area.x = draggable->actual_position.x;
        draggable->area.y = draggable->actual_position.y;
    }
}

void
draw_draggable (draggable *draggable) {
    const float area_lines_thickness = 30.0f;
    Color area_color = draggable->is_selected ? GREEN : RED;
    DrawRectangleLinesEx(draggable->area, area_lines_thickness, area_color);
}

void
reset_draggable (draggable *draggable) {
    draggable->is_selected = false;
    draggable->actual_position = draggable->original_position;

    // Ok?
    draggable->area.x = draggable->actual_position.x;
    draggable->area.y = draggable->actual_position.y;

    draggable->state = DRAGGABLE_IDLE;
}