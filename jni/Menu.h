
bool titleValid = false, headingValid = false, iconValid = false;

void *antiLeech(void *) {
    sleep(15);
    if (!titleValid || !headingValid || !iconValid) {
        //Bad function to make it crash
        int *p = 0;
        *p = 0;
    }
    return NULL;
}

void setText(JNIEnv *env, jobject obj, const char* text){
    //https://stackoverflow.com/a/33627640/3763113
    //A little JNI calls here. You really really need a great knowledge if you want to play with JNI stuff
    //Html.fromHtml("");
    jclass html = (*env).FindClass(OBFUSCATE("android/text/Html"));
    jmethodID fromHtml = (*env).GetStaticMethodID(html, OBFUSCATE("fromHtml"), OBFUSCATE("(Ljava/lang/String;)Landroid/text/Spanned;"));

    //setText("");
    jclass textView = (*env).FindClass(OBFUSCATE("android/widget/TextView"));
    jmethodID setText = (*env).GetMethodID(textView, OBFUSCATE("setText"), OBFUSCATE("(Ljava/lang/CharSequence;)V"));

    //Java string
    jstring jstr = (*env).NewStringUTF(text);
    (*env).CallVoidMethod(obj, setText,  (*env).CallStaticObjectMethod(html, fromHtml, jstr));
}

extern "C" {
JNIEXPORT void JNICALL
Java_android_support_putri_Loader_setTitleText(JNIEnv *env, jobject thiz, jobject obj) {
    setText(env, obj, OBFUSCATE("<b>MaSuKi</b>"));

    titleValid = true;
}

JNIEXPORT void JNICALL
Java_android_support_putri_Loader_setHeadingText(JNIEnv *env, jobject thiz, jobject obj) {
    setText(env, obj, OBFUSCATE("<p style=\"color:green;\">@RSM_FML_MODS3</p>"));

    headingValid = true;
}

JNIEXPORT jstring
JNICALL
Java_android_support_putri_Loader_Icon(JNIEnv *env, jobject thiz) {
    iconValid = true;

    //Use https://www.base64encode.org/ to encode your image to base64
    return env->NewStringUTF(
            OBFUSCATE("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"));
            }

JNIEXPORT jstring
JNICALL
Java_android_support_putri_Loader_IconWebViewData(JNIEnv *env, jobject thiz) {
    iconValid = true;
    
    return NULL;
}

JNIEXPORT jobjectArray
JNICALL
Java_android_support_putri_Loader_settingsList(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_Settings"),
            OBFUSCATE("-1_Toggle_Color animation"),
            OBFUSCATE("-2_Toggle_Auto size vertically"),
            OBFUSCATE(
                    "-3_Toggle_Save feature preferences (Radio Button is not saved)"), //-3 is checked on Preferences.java
            OBFUSCATE("Category_Logcat"),
            OBFUSCATE(
                    "RichTextView_Save logcat if a bug occured and sent it to the modder. Clear logcat and reproduce bug again if the log file is too large"),
            OBFUSCATE(
                    "RichTextView_<small>Saving logcat does not need file permission. Logcat location:<br/>Android 11: /storage/emulated/0/Documents/Mod Menu logs/"
                    "<br/>Android 10 and below: /storage/emulated/0/Android/data/(package name)/files/Mod Menu logs</small>"),
            OBFUSCATE("-4_Button_Save logcat to file"),
            OBFUSCATE("-5_Button_Clear logcat"),
            OBFUSCATE("Category_Menu"),
            OBFUSCATE("-6_Button_<font color='red'>Close settings</font>"),
    };

    int Total_Feature = (sizeof features /
                         sizeof features[0]); //Now you dont have to manually update the number everytime;
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}
}
