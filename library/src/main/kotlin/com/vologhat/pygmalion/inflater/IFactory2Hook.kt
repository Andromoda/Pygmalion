package com.vologhat.pygmalion.inflater

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View

typealias OnCreateViewWithParent=(parent:View?,name:String,context:Context,attrs:AttributeSet) -> View?
typealias OnCreateView=(name:String,context:Context,attrs:AttributeSet) -> View?

interface IFactory2Hook
    :LayoutInflater.Factory2
{
    val force:Boolean
        get()=false
    
    override fun onCreateView(
        parent:View?,
        name:String,
        context:Context,
        attrs:AttributeSet,
    ):View?=null
    
    override fun onCreateView(
        name:String,
        context:Context,
        attrs:AttributeSet,
    ):View?=null
}

class Factory2HookBuilder internal constructor(private var force:Boolean)
{
    private var onCreateViewWithParent:OnCreateViewWithParent?=null
    private var onCreateView:OnCreateView?=null
    
    @JvmSynthetic
    fun onCreateViewWithParent(onCreateViewWithParent:OnCreateViewWithParent)
    {
        this.onCreateViewWithParent=onCreateViewWithParent
    }
    
    @JvmSynthetic
    fun onCreateView(onCreateView:OnCreateView)
    {
        this.onCreateView=onCreateView
    }
    
    @JvmSynthetic
    fun build()=
        object:IFactory2Hook
        {
            override val force=this@Factory2HookBuilder.force
            
            override fun onCreateView(
                parent:View?,
                name:String,
                context:Context,
                attrs:AttributeSet,
            )=onCreateViewWithParent?.invoke(parent,name,context,attrs)
                ?: onCreateView(name,context,attrs)
            
            override fun onCreateView(
                name:String,
                context:Context,
                attrs:AttributeSet,
            )=onCreateView?.invoke(name,context,attrs)
        }
}

@JvmSynthetic
fun factory2Hook(force:Boolean=false,block:Factory2HookBuilder.() -> Unit)=
    Factory2HookBuilder(force).apply(block).build()