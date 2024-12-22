@file:Suppress("KotlinJniMissingFunction")

package com.vologhat.pygmalion.utils

import android.annotation.SuppressLint
import sun.misc.Unsafe
import java.util.Objects

/** Unsafe instance used to get/modify natively allocated data */
@SuppressLint("DiscouragedPrivateApi")
@JvmField
internal val UNSAFE=Unsafe::class.java.getDeclaredMethod("getUnsafe").invoke("null") as Unsafe

/** The interface describing interaction with natively primitives to use it in Java layer */
sealed interface NativeArray<T>
{
    /** Base allocation address */
    val baseAddr:Long
    
    /** Length of allocated primitive array */
    val length:Int
    
    operator fun get(index:Int):T
    operator fun set(index:Int,value:T)
}

class NativeByteArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Byte>
{
    override fun get(index:Int)=
        UNSAFE.getByte(baseAddr+Objects.checkIndex(index,length)*SCALE)
    
    override fun set(index:Int,value:Byte)
    {
        UNSAFE.putByte(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(ByteArray::class.java)
    }
}

class NativeShortArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Short>
{
    override fun get(index:Int)=
        UNSAFE.getShort(baseAddr+Objects.checkIndex(index,length)*SCALE)
    
    override fun set(index:Int,value:Short)
    {
        UNSAFE.putShort(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(ShortArray::class.java)
    }
}

class NativeCharArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Char>
{
    override fun get(index:Int)=
        UNSAFE.getChar(baseAddr+Objects.checkIndex(index,length)*SCALE)
    
    override fun set(index:Int,value:Char)
    {
        UNSAFE.putChar(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(CharArray::class.java)
    }
}

class NativeIntArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Int>
{
    override fun get(index:Int)=
        UNSAFE.getInt(baseAddr+Objects.checkIndex(index,length)*SCALE)
    
    override fun set(index:Int,value:Int)
    {
        UNSAFE.putInt(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(IntArray::class.java)
    }
}

class NativeLongArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Long>
{
    override fun get(index:Int)=
        UNSAFE.getLong(baseAddr+Objects.checkIndex(index,length)*SCALE)
    
    override fun set(index:Int,value:Long)
    {
        UNSAFE.putLong(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(LongArray::class.java)
    }
}

class NativeFloatArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Float>
{
    override fun get(index:Int)=
        UNSAFE.getFloat(baseAddr+Objects.checkIndex(index,length)*SCALE)
    
    override fun set(index:Int,value:Float)
    {
        UNSAFE.putFloat(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(FloatArray::class.java)
    }
}

class NativeDoubleArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Double>
{
    override fun get(index:Int)=
        UNSAFE.getDouble(baseAddr+Objects.checkIndex(index,length)+SCALE)
    
    override fun set(index:Int,value:Double)
    {
        UNSAFE.putDouble(baseAddr+Objects.checkIndex(index,length)*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(DoubleArray::class.java)
    }
}