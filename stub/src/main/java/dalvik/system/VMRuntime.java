/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package dalvik.system;

import dalvik.annotation.optimization.FastNative;

/**
 * Provides an interface to VM-global, Dalvik-specific features.
 * An application cannot create its own Runtime instance, and must obtain
 * one from the getRuntime method.
 *
 * @hide
 * @noinspection ALL
 */
public final class VMRuntime {

    public boolean is64Bit() {
        return false;
    }

    /**
     * Returns the object that represents the current runtime.
     * @return the runtime object
     *
     * @hide
     */
    public static VMRuntime getRuntime() {
        return null;
    }

    /**
     * Sets the list of exemptions from hidden API access enforcement.
     *
     * @param signaturePrefixes
     *         A list of signature prefixes. Each item in the list is a prefix match on the type
     *         signature of a blacklisted API. All matching APIs are treated as if they were on
     *         the whitelist: access permitted, and no logging..
     *
     * @hide
     */
    public native void setHiddenApiExemptions(String[] signaturePrefixes);

    /**
     * Returns an array allocated in an area of the Java heap where it will never be moved.
     * This is used to implement native allocations on the Java heap, such as DirectByteBuffers
     * and Bitmaps.
     *
     * @param componentType the component type of the returned array.
     * @param length the length of the returned array.
     * @return array allocated in an area of the heap where it will never be moved.
     *
     * @hide
     */
    @FastNative
    public native Object newNonMovableArray(Class<?> componentType, int length);

    /**
     * Returns an array of at least {@code minLength}, but potentially larger. The increased size
     * comes from avoiding any padding after the array. The amount of padding varies depending on
     * the componentType and the memory allocator implementation.
     *
     * @param componentType the component type of the returned array.
     * @param minLength     the minimum length of the returned array. The actual length could
     *                      be greater.
     * @return              array of at least of {@code minLength}
     *
     * @hide
     */
    @FastNative
    public native Object newUnpaddedArray(Class<?> componentType, int minLength);

    /**
     * Returns the address of {@code array[0]}. This differs from using JNI in that JNI
     * might lie and give you the address of a copy of the array when in forcecopy mode.
     *
     * @param array the object we want the native address of. Must be a non-movable
     * primitive array.
     * @return native address of {@code array[0]}.
     *
     * @hide
     */
    @FastNative
    public native long addressOf(Object array);
}