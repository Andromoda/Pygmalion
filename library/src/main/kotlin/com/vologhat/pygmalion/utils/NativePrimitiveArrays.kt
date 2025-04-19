@file:Suppress("KotlinJniMissingFunction")

package com.vologhat.pygmalion.utils

import android.annotation.SuppressLint
import sun.misc.Unsafe

/** Unsafe instance used to get/modify natively allocated data */
@SuppressLint("DiscouragedPrivateApi")
@JvmField
internal val UNSAFE=Unsafe::class.java.getDeclaredMethod("getUnsafe").invoke(null) as Unsafe

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

/** Wrapper to work with natively allocated [Byte] array */
class NativeByteArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Byte>
{
    override fun get(index:Int)=
        UNSAFE.getByte(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Byte)
    {
        UNSAFE.putByte(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(ByteArray::class.java)
    }
}

/** Wrapper to work with natively allocated [Short] array */
class NativeShortArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Short>
{
    override fun get(index:Int)=
        UNSAFE.getShort(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Short)
    {
        UNSAFE.putShort(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(ShortArray::class.java)
    }
}

/** Wrapper to work with natively allocated [Char] array */
class NativeCharArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Char>
{
    override fun get(index:Int)=
        UNSAFE.getChar(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Char)
    {
        UNSAFE.putChar(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(CharArray::class.java)
    }
}

/** Wrapper to work with natively allocated [Int] array */
class NativeIntArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Int>
{
    override fun get(index:Int)=
        UNSAFE.getInt(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Int)
    {
        UNSAFE.putInt(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(IntArray::class.java)
    }
}

/** Wrapper to work with natively allocated [Long] array */
class NativeLongArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Long>
{
    override fun get(index:Int)=
        UNSAFE.getLong(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Long)
    {
        UNSAFE.putLong(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(LongArray::class.java)
    }
}

/** Wrapper to work with natively allocated [Float] array */
class NativeFloatArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Float>
{
    override fun get(index:Int)=
        UNSAFE.getFloat(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Float)
    {
        UNSAFE.putFloat(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(FloatArray::class.java)
    }
}

/** Wrapper to work with natively allocated [Double] array */
class NativeDoubleArray(
    override val baseAddr:Long,
    override val length:Int,
):NativeArray<Double>
{
    override fun get(index:Int)=
        UNSAFE.getDouble(baseAddr+index*SCALE)
    
    override fun set(index:Int,value:Double)
    {
        UNSAFE.putDouble(baseAddr+index*SCALE,value)
    }
    
    companion object
    {
        @JvmField
        val SCALE=UNSAFE.arrayIndexScale(DoubleArray::class.java)
    }
}