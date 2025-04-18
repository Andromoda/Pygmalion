package com.vologhat.pygmalion.inflater

import android.content.Context
import android.util.AttributeSet
import android.view.LayoutInflater
import android.view.View

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

