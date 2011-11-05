/**************************************************/
/*                                                */
/*  Draw Header Aufgabe 2                         */
/*                                                */
/**************************************************/
/*  Authors:                Reto Bollinger        */
/*                          bolliret@zhwin.ch     */
/*                                                */
/*                          Hanspeter Brühlmann   */
/*                          bruehhan@zhwin.ch     */
/*                                                */
/**************************************************/
/*  Date:                   15. October 2004      */
/**************************************************/

#ifndef _DRAW_H
#define _DRAW_H

/**************************************************/
/* Variable definition                            */
/**************************************************/

extern float fps;									// Frames per second
extern float dist;

/**************************************************/
/* Function definition                            */
/**************************************************/

void draw3D( );

void draw_screen( );

void countFrames( );

void camera( );

void incAnimationVars( );

void drawShip( );

void drawGrid( );

#endif
