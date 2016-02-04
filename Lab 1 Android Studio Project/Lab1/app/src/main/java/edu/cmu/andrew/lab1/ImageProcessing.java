package edu.cmu.andrew.lab1;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.provider.MediaStore.MediaColumns;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.support.v7.app.AppCompatActivity;

import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;
import org.opencv.core.*;
import org.opencv.android.*;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;

import android.util.Log;

public class ImageProcessing extends AppCompatActivity {

    int SELECT_FILE = 1;
    Button btnSelect;
    ImageView ivImage;

    static {
        if (!OpenCVLoader.initDebug()) {
            // Handle initialization error
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        Mat x = new Mat();

        setContentView(R.layout.activity_image_processing);
        btnSelect = (Button) findViewById(R.id.btnSelectPhoto);
        btnSelect.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                selectImage();
            }
        });
        ivImage = (ImageView) findViewById(R.id.ivImage);

    }


    private void selectImage() {
        final CharSequence[] items = { "Choose from Library",
                "Cancel" };

        AlertDialog.Builder builder = new AlertDialog.Builder(ImageProcessing.this);
        builder.setTitle("Add Photo!");
        builder.setItems(items, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int item) {
                if (items[item].equals("Choose from Library")) {
                    Intent intent = new Intent(
                            Intent.ACTION_PICK,
                            android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
                    intent.setType("image/*");
                    startActivityForResult(
                            Intent.createChooser(intent, "Select File"),
                            SELECT_FILE);
                } else if (items[item].equals("Cancel")) {
                    dialog.dismiss();
                }
            }
        });
        builder.show();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == Activity.RESULT_OK) {
            if (requestCode == SELECT_FILE)
                onSelectFromGalleryResult(data);

        }
    }



    @SuppressWarnings("deprecation")
    private void onSelectFromGalleryResult(Intent data) {
        Uri selectedImageUri = data.getData();
        String[] projection = { MediaColumns.DATA };
        Cursor cursor = managedQuery(selectedImageUri, projection, null, null,
                null);
        int column_index = cursor.getColumnIndexOrThrow(MediaColumns.DATA);
        cursor.moveToFirst();

        String selectedImagePath = cursor.getString(column_index);

        final Bitmap bm;
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeFile(selectedImagePath, options);
        final int REQUIRED_SIZE = 200;
        int scale = 1;
        while (options.outWidth / scale / 2 >= REQUIRED_SIZE
                && options.outHeight / scale / 2 >= REQUIRED_SIZE)
            scale *= 2;
        options.inSampleSize = scale;
        options.inJustDecodeBounds = false;
        bm = BitmapFactory.decodeFile(selectedImagePath, options);

        ivImage.setImageBitmap(bm);

        Button blurButton;
        blurButton = (Button)findViewById(R.id.blur);
        blurButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {
                Bitmap processedImage;
                Mat src = new Mat(bm.getHeight(), bm.getWidth(), CvType.CV_8UC4);
                Utils.bitmapToMat(bm, src);
                Imgproc.blur(src, src, new Size(5, 5));
                processedImage = Bitmap.createBitmap(src.cols(), src.rows(),
                        Bitmap.Config.ARGB_8888);
                Utils.matToBitmap(src, processedImage);
                ivImage.setImageBitmap(processedImage);
            }
        });
        
        Button cannyButton;
        cannyButton = (Button)findViewById(R.id.canny);
        cannyButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View arg0) {
                Bitmap processedImage;
                Mat src = new Mat(bm.getHeight(), bm.getWidth(), CvType.CV_8UC4);
                Utils.bitmapToMat(bm, src);
                //Imgproc.canny(src, src, 10, 100, 3);
                processedImage = Bitmap.createBitmap(src.cols(), src.rows(),
                        Bitmap.Config.ARGB_8888);
                Utils.matToBitmap(src, processedImage);
                ivImage.setImageBitmap(processedImage);
            }
        });
    }


}