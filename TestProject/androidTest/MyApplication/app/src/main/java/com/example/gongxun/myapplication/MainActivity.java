package com.example.gongxun.myapplication;

import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private Handler mHandler = null;

    private static final int OVERLAY_PERMISSION_REQ_CODE =10005 ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHandler = new Handler();

        Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {


                mHandler.postDelayed(new Runnable() {

                    @Override
                    public void run() {
                        if(Settings.canDrawOverlays(MainActivity.this))
                        {
//有悬浮窗权限开启服务绑定 绑定权限
                            WindowUtils.showPopupWindow(MainActivity.this);
                            Log.d("test", "test01");

                        }else{
//没有悬浮窗权限m,去开启悬浮窗权限
                            try{
                                Intent  intent=new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION);
                                startActivityForResult(intent, OVERLAY_PERMISSION_REQ_CODE);
                            }catch (Exception e)
                            {
                                e.printStackTrace();
                            }


                        }
                    }
                }, 1000 * 3);

            }
        });
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == OVERLAY_PERMISSION_REQ_CODE) {
            if(Build.VERSION.SDK_INT>=23) {
                if (!Settings.canDrawOverlays(this)) {
                    Toast.makeText(this, "权限授予失败，无法开启悬浮窗", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(this, "权限授予成功！", Toast.LENGTH_SHORT).show();
                }
            }
        }
    }
}
