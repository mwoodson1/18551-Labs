package edu.cmu.andrew.lab2;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    Button cameraButton, optionsButton, viewButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        if (!OpenCVLoader.initDebug()) {
            Log.e(this.getClass().getSimpleName(), "  OpenCVLoader.initDebug(), not working.");
        } else {
            Log.d(this.getClass().getSimpleName(), "  OpenCVLoader.initDebug(), working.");
        }

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        cameraButton = (Button)findViewById(R.id.cameraButton);
        cameraButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {
                Intent videoProcessingIntent = new Intent(MainActivity.this, VideoProcessingActivity.class);
                startActivity(videoProcessingIntent);
            }
        });

        optionsButton = (Button)findViewById(R.id.optionsButton);
        optionsButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {
                Intent optionsIntent = new Intent(MainActivity.this, ListViewActivity.class);
                startActivity(optionsIntent);
            }
        });

        viewButton = (Button)findViewById(R.id.viewButton);
        viewButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {
                Intent viewIntent = new Intent(MainActivity.this, OverlayActivity.class);
                startActivity(viewIntent);
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }
        Mat x = new Mat();
        return super.onOptionsItemSelected(item);
    }
}
