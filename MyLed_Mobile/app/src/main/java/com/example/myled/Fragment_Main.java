package com.example.myled;

import android.graphics.Bitmap;
import android.graphics.Color;
import android.os.Bundle;

import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

public class Fragment_Main extends Fragment {
    ConstraintLayout home_layout;
    SeekBar brightness_seekBar;
    ImageView colorPicker, cursor;
    Bitmap bitmap;
    ImageButton on_off_button;
    TextView tV_brightness;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment__main, container, false);

        home_layout = view.findViewById(R.id.home_layout);


        brightness_seekBar = view.findViewById(R.id.brightness_seekBar);
        on_off_button = view.findViewById(R.id.on_off_button);
        tV_brightness = view.findViewById(R.id.tV_brightness);

        cursor = view.findViewById(R.id.cursor_imageView);
        colorPicker = view.findViewById(R.id.color_imageView);
        colorPicker.setDrawingCacheEnabled(true);
        colorPicker.buildDrawingCache(true);

        if(Memory.theme == 0){
            on_off_button.setImageDrawable(getResources().getDrawable(R.drawable.power_off_2));
            brightness_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb));
            brightness_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar));
            home_layout.setBackgroundColor(getResources().getColor(R.color.dark));
            tV_brightness.setTextColor(getResources().getColor(R.color.grey));
        }else{
            on_off_button.setImageDrawable(getResources().getDrawable(R.drawable.power_off_2_white));
            brightness_seekBar.setThumb(getResources().getDrawable(R.drawable.seekbar_thumb_white));
            brightness_seekBar.setProgressDrawable(getResources().getDrawable(R.drawable.seekbar_white));
            home_layout.setBackgroundColor(getResources().getColor(R.color.light));
            tV_brightness.setTextColor(getResources().getColor(R.color.grey_light));
        }

        brightness_seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener(){
            @Override
            public void onProgressChanged(SeekBar brightness_seekBar, int progress, boolean fromUser) {
                byte[] tx_data = new byte[2];
                tx_data[0] = Commands.SET_BRIGHTNESS;
                Memory.brightness = brightness_seekBar.getProgress();
                tx_data[1] = (byte)Memory.brightness;
                DataSender ds = new DataSender();
                ds.execute(tx_data);
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }
        });
        colorPicker.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                try {
                    if(motionEvent.getAction() == MotionEvent.ACTION_DOWN || motionEvent.getAction() == MotionEvent.ACTION_MOVE){
                        bitmap = colorPicker.getDrawingCache();
                        int pixels = bitmap.getPixel((int)motionEvent.getX(), (int)motionEvent.getY());

                        int r = Color.red(pixels);
                        int g = Color.green(pixels);
                        int b = Color.blue(pixels);

                        if((r + g + b) != 0) {
                            cursor.setX(motionEvent.getX() - cursor.getWidth() / 2);
                            cursor.setY(motionEvent.getY() - cursor.getHeight() / 2);
                            byte[] tx_data = new byte[4];
                            tx_data[0] = Commands.SET_COLOR;
                            Memory.color_r = r;
                            Memory.color_g = g;
                            Memory.color_b = b;
                            tx_data[1] = (byte) Memory.color_r;
                            tx_data[2] = (byte) Memory.color_g;
                            tx_data[3] = (byte) Memory.color_b;
                            DataSender ds = new DataSender();
                            ds.execute(tx_data);
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }

                return true;
            }
        });

        on_off_button.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if(motionEvent.getAction() == MotionEvent.ACTION_DOWN){
                    if(Memory.theme == 0)
                        on_off_button.setImageDrawable(getResources().getDrawable(R.drawable.power_on_2));
                    else
                        on_off_button.setImageDrawable(getResources().getDrawable(R.drawable.power_on_2_white));

                    byte[] tx_data = new byte[1];
                    tx_data[0] = Commands.ON_OFF;
                    DataSender ds = new DataSender();
                    ds.execute(tx_data);
                } else if(motionEvent.getAction() == MotionEvent.ACTION_UP){
                    if(Memory.theme == 0)
                        on_off_button.setImageDrawable(getResources().getDrawable(R.drawable.power_off_2));
                    else
                        on_off_button.setImageDrawable(getResources().getDrawable(R.drawable.power_off_2_white));
                }
                return false;
            }
        });

        brightness_seekBar.setProgress(Memory.brightness);

        return view;
    }
}