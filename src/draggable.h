#ifndef DRAGGABLE_H
#define DRAGGABLE_H

typedef enum draggable_state {
    DRAGGABLE_IDLE,
    DRAGGABLE_DRAGGING,
    DRAGGABLE_RESETTING,
} draggable_state;

typedef struct draggable {
    Vector2 original_position;
    Vector2 actual_position;
    Rectangle area;
    draggable_state state;
    bool is_selected;
} draggable;

// Creates a new draggable object
draggable create_draggable (const Vector2 position, const Vector2 size);

// Update draggable logic
void update_draggable (draggable * draggable);

// Draw draggable area rectangle (ideal for debuging)
void draw_draggable (draggable * draggable);

// Resets draggable position to its original position
void reset_draggable (draggable * draggable);

#endif // DRAGGABLE_H