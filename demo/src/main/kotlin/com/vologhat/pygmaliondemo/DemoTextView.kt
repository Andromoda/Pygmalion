package com.vologhat.pygmaliondemo

import android.content.Context
import android.util.AttributeSet
import androidx.appcompat.widget.AppCompatTextView

class DemoTextView
    :AppCompatTextView
{
    constructor(context:Context)
            :super(context)
    
    constructor(context:Context,attrs:AttributeSet?)
            :super(context,attrs)
    
    constructor(context:Context,attrs:AttributeSet?,defStyleAttr:Int)
            :super(
        context,
        attrs,
        defStyleAttr
    )
}
