#include "Wall.h"

Wall::Wall() {
    length = 0;
    addPoint( Input::mouseX, Input::mouseY );
}

void Wall::update() {
    editedPoint->x = Input::mouseX;
    editedPoint->y = Input::mouseY;
}

void Wall::draw() {
    glColor3f( 1, 1, 1 );
    glBegin( GL_LINES );
    WallPoint *curPoint = front;
    while( curPoint != editedPoint ) {
        glVertex2f( curPoint->x, curPoint->y );
        glVertex2f( curPoint->next->x, curPoint->next->y );
        curPoint = curPoint->next;
    }
    glEnd();
}

void Wall::addPoint( int x, int y ) {
    //We know the front and the back
    //Add to the back
    //editedPoint is ALWAYS the last point, until Wall::editing is false
    switch( length ) {
    case 0:
        front = new WallPoint( x, y );
        front->next = editedPoint;
        back = editedPoint;
        length++;
        break;
    case 1:
        WallPoint *p = new WallPoint( x, y );
        front->next = p;

    }
}