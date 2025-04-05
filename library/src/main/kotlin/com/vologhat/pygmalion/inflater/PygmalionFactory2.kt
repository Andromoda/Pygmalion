package com.vologhat.pygmalion.inflater

import android.content.Context
import android.util.AttributeSet
import android.util.Log
import android.view.LayoutInflater
import android.view.View

typealias TargetClass=Class<out Context>

class PygmalionFactory2 internal constructor(
    internal val original:LayoutInflater.Factory2?=null,
):LayoutInflater.Factory2
{
    private val hooksMap=mutableMapOf<TargetClass,MutableSet<IFactory2Hook>>()
    
    fun registerHooks(target:TargetClass,vararg hooks:IFactory2Hook)
    {
        hooksMap.getOrPut(target) { mutableSetOf() }.addAll(hooks)
    }
    
    fun registerHook(hook:IFactory2Hook,vararg targets:TargetClass)
    {
        targets.forEach { target ->
            hooksMap.getOrPut(target) { mutableSetOf() }.add(hook)
        }
    }
    
    fun unregisterHooks(target:TargetClass,vararg hooks:IFactory2Hook)
    {
        hooksMap[target]?.removeAll(hooks)
    }
    
    fun unregisterHook(hook:IFactory2Hook,vararg targets:TargetClass)
    {
        targets.forEach { target ->
            hooksMap[target]?.remove(hook)
        }
    }
    
    fun unregisterAllHooks(target:TargetClass)
    {
        hooksMap.remove(target)
    }
    
    override fun onCreateView(
        parent:View?,
        name:String,
        context:Context,
        attrs:AttributeSet,
    ):View?
    {
        hooksMap[context::class.java]?.forEach { hook ->
            val view=hook.onCreateView(parent,name,context,attrs)
            if(view!==null||hook.force) return view
        }
        return original?.onCreateView(parent,name,context,attrs)
    }
    
    override fun onCreateView(
        name:String,
        context:Context,
        attrs:AttributeSet,
    ):View?
    {
        hooksMap[context::class.java]?.forEach { hook ->
            val view=hook.onCreateView(name,context,attrs)
            if(view!==null||hook.force) return view
        }
        return original?.onCreateView(name,context,attrs)
    }
}
