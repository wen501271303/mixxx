/***************************************************************************
                          visualbuffer.h  -  description
                             -------------------
    copyright            : (C) 2002 by Tue and Ken Haste Andersen and Kenny 
                                       Erleben
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is fr ee software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef VISUALBUFFER_H
#define VISUALBUFFER_H

/** Display rate in Hz. This relates to the display resolution */
const int DISPLAYRATE = 2000;

/**
  * A Signal Vertex Array Buffer.
  * This class is capable of preprosseing a
  * signal into a 3D representation and plotting it.
  *
  * Each signal value is transformed into a 3D
  * point. The signal is plotted using the draw method, usually invoked from
  * a VisualDisplayBuffer class.
  */

#include "../defs.h"
#include <qobject.h>
#include <qgl.h>

class ReaderExtract;
class ControlPotmeter;

typedef struct
{
    float           *p1, *p2;
    int             len1, len2;
} bufInfo;

class VisualBuffer : public QObject
{
public:
    VisualBuffer(ReaderExtract *pReaderExtract, ControlPotmeter *pPlaypos);
    virtual ~VisualBuffer();
    /** Update and resample signal vertex buffer */
    virtual void update(int iPos) = 0;
    /** Draw the buffer */
    virtual void draw(GLfloat *p, int iLen) = 0;

    bufInfo getVertexArray();
    int getBufferLength();
    int getDisplayLength();
    GLfloat *getBasePtr();

protected:
    /** Memory Allocation Routine.
      *  @param size    The size (#floats) of the vertex array
      *  @return        A pointer to the allocated vertex array.
      */
    GLfloat *allocate(int iSize);
    /** Auxiliary Method.
      * This is used to validate the error state of openGL.
      */
    void validate();

    /** Pointer to ControlPotmeter holding buffer play position in ReaderExtractWave */
    ControlPotmeter *m_pPlaypos;
    /** Pointer to the actual buffer, an openGL vertex array */
    GLfloat *m_pBuffer;
    /** Pointer to source buffer from ReaderExtract */
    CSAMPLE *m_pSource;
    /** The total number of samples in the buffer m_pBuffer. */
    int m_iLen;
    /** The total number of samples in the buffer m_pSource. */
    int m_iSourceLen;
    /** Resample factor determining the factor to reduce the incomming signal with */
    CSAMPLE m_fResampleFactor;
    /** Factor used in convesion of position and length to the assigned ReaderExtract
      * position */
    CSAMPLE m_fPositionFactor;
    /** Number of samples to display (used in getVertexArray) */             
    int m_iDisplayLen;
    /** Pounter to ReaderExtract */
    ReaderExtract *m_pReaderExtract;
};
#endif



