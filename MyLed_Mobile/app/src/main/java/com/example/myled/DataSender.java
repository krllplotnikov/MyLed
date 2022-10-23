package com.example.myled;

import android.os.AsyncTask;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

class DataSender extends AsyncTask<byte[], Void, Void>
{

    @Override
    protected Void doInBackground(byte[]... voids) {
        byte[] data = voids[0];
        try {
            Socket s0 = new Socket("192.168.0.113", 1305);
            OutputStream outToServer0 = s0.getOutputStream();
            DataOutputStream out0 = new DataOutputStream(outToServer0);
            out0.write(data);
            s0.close();
        } catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }
}
