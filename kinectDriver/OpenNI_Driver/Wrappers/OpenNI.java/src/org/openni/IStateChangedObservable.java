/*****************************************************************************
*                                                                            *
*  OpenNI 1.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
package org.openni;

/**
 * Extends IObservable interface to include state change events. <BR><BR>
 * 
 * This interface is intended to extend the IObservable interface to deal 
 * specifically with state change events.  It is currently a completely 
 * empty interface, so implementing IStateChangedObservable is identical to 
 * implementing IObservable.  In the future, this may change to handle
 * any interface elements specific to StateChange events.
 *
 */
public interface IStateChangedObservable extends IObservable<EventArgs> 
{
}
