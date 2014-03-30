package com.javacodegeeks.android.bluetoothtest;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.util.Set;
import java.util.UUID;

import android.content.Intent;
import android.content.IntentFilter;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Toast;


public class MainActivity extends Activity {
	
   private static final int REQUEST_ENABLE_BT = 1;
   private Button onBtn;
   private Button offBtn;
   private Button listBtn;
   private Button findBtn;
   private Button btnRed;
   private Button btnGreen;
   private Button btnBlue;
   private Button btnSend;
   private Button btnOff;
   private Button processDevices;
   private TextView text;
   private EditText editTextSend;
   private BluetoothAdapter myBluetoothAdapter;
   private Set<BluetoothDevice> pairedDevices;
   private ListView myListView;
   private ArrayAdapter<String> BTArrayAdapter;
   
   private OutputStream mmOutputStream;	
   private InputStream mmInputStream;
   private BluetoothDevice mmDevice;
   private BluetoothSocket mmSocket;
   private String chosenOne; // Device Name that has been chosen
   
   private volatile boolean stopWorker;
   private Thread workerThread;
   private byte[] readBuffer;
   private int readBufferPosition;


   void sendMsg (String msg) {
       if (mmDevice == null)
    	   text.setText("Connect first");
       else {    	   
          try {
   	         mmOutputStream.write(msg.getBytes());
          } catch (IOException ex) { }
          text.setText("Sent " + msg);
       }   
	   
   }
   
   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.activity_main);
      mmDevice = null;
      chosenOne = null;
      
      // take an instance of BluetoothAdapter - Bluetooth radio
      myBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
      if(myBluetoothAdapter == null) {
    	  onBtn.setEnabled(false);
    	  offBtn.setEnabled(false);
    	  listBtn.setEnabled(false);
    	  findBtn.setEnabled(false);
    	  text.setText("Status: not supported");
    	  
    	  Toast.makeText(getApplicationContext(),"Your device does not support Bluetooth",
         		 Toast.LENGTH_LONG).show();
      } else {
	      text = (TextView) findViewById(R.id.text);
	      editTextSend = (EditText) findViewById(R.id.editTextSend);
	      onBtn = (Button)findViewById(R.id.turnOn);
	      onBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				on(v);
			}
	      });
	      
	      offBtn = (Button)findViewById(R.id.turnOff);
	      offBtn.setOnClickListener(new OnClickListener() {
	  		
	  		@Override
	  		public void onClick(View v) {
	  			// TODO Auto-generated method stub
	  			off(v);
	  		}
	      });
	      
	      btnSend = (Button)findViewById(R.id.btnSend);
	      btnSend.setOnClickListener(new OnClickListener(){
	    	 public void onClick (View v) {
	    		 sendMsg (editTextSend.getText().toString() + "\n");
	    	 }
	      });
	      
	      btnRed = (Button)findViewById(R.id.btnRed);
	      btnRed.setOnClickListener(new OnClickListener() {
	    	  public void onClick (View v) {
	    		  sendMsg ( "Red\n");
	    	  }
	      });
	      
	      btnGreen = (Button)findViewById(R.id.btnGreen);
	      btnGreen.setOnClickListener(new OnClickListener() {
	    	  public void onClick (View v) {
	    		  sendMsg ( "Green\n");
	    	  }
	      });
	      
	      btnOff = (Button)findViewById(R.id.btnOff);
	      btnOff.setOnClickListener(new OnClickListener() {
	    	  public void onClick (View v) {
	    		  sendMsg ( "Off\n");
	    	  }
	      });
	      
	      btnBlue = (Button)findViewById(R.id.btnBlue);
	      btnBlue.setOnClickListener(new OnClickListener() {
	    	  public void onClick (View v) {
	    		  sendMsg ( "Blue\n");
	    	  }
	      });
	      
	      findBtn = (Button)findViewById(R.id.search);
	      findBtn.setOnClickListener(new OnClickListener() {
	  		
	  		@Override
	  		public void onClick(View v) {
	  			// TODO Auto-generated method stub
	  			find(v);
	  		}
	      });
	      	      	    
	      myListView = (ListView)findViewById(R.id.listView1);
	
	      // create the arrayAdapter that contains the BTDevices, and set it to the ListView
	      BTArrayAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
	      myListView.setAdapter(BTArrayAdapter);
	      
	      myListView.setOnItemClickListener(new OnItemClickListener() {
	    	  public void onItemClick (AdapterView<?> parent, View view,
	    			                   int position, long id) {
	    		  // Set mmDevice
	    		  
	    		  String adapter = ((TextView) view).getText().toString();
	    		  mmDevice = null;
	    		  text.setText(adapter);
	    		  chosenOne = adapter;
  	   		      myBluetoothAdapter.cancelDiscovery();
  	   		      
    		 	  BTArrayAdapter.clear();
  				  myBluetoothAdapter.startDiscovery();
  	  		      text.setText ( "Start Discovery Again");
  				  registerReceiver(bReceiver, new IntentFilter(BluetoothDevice.ACTION_FOUND));	
  	   		      
	    	  }
	      });
	      
      }
   }
   

   public void on(View view){
      if (!myBluetoothAdapter.isEnabled()) {
         Intent turnOnIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
         startActivityForResult(turnOnIntent, REQUEST_ENABLE_BT);

         Toast.makeText(getApplicationContext(),"Bluetooth turned on" ,
        		 Toast.LENGTH_LONG).show();
      }
      else{
         Toast.makeText(getApplicationContext(),"Bluetooth is already on",
        		 Toast.LENGTH_LONG).show();
      }
   }
   
   @Override
   protected void onActivityResult(int requestCode, int resultCode, Intent data) {
	   // TODO Auto-generated method stub
	   if(requestCode == REQUEST_ENABLE_BT){
		   if(myBluetoothAdapter.isEnabled()) {
			   text.setText("Status: Enabled");
		   } else {   
			   text.setText("Status: Disabled");
		   }
	   }
   }
   
   final BroadcastReceiver bReceiver = new BroadcastReceiver() {
	    public void onReceive(Context context, Intent intent) {
	        String action = intent.getAction();
	        String name;
	        Integer index;
	        // When discovery finds a device
	        if (BluetoothDevice.ACTION_FOUND.equals(action)) {
	             // Get the BluetoothDevice object from the Intent
	        	 BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
	        	 // add the name and the MAC address of the object to the arrayAdapter
	             BTArrayAdapter.add(device.getName() + "\n" + device.getAddress());
	             BTArrayAdapter.notifyDataSetChanged();
	             
	        	 if ((chosenOne != null) && (mmDevice == null)) {	        		 
	        		 index = chosenOne.indexOf("\n");
	        		 if (index > -1) {	        			 
   	        		    name = chosenOne.substring(0,index);
	        		    if (name.compareTo(device.getName()) == 0) {
   	        	            mmDevice = device;
   	        	            text.setText ( "device set");
   	       	   		        myBluetoothAdapter.cancelDiscovery();
   	 	                    try {
   		                       openBT();
   		                    }
   		                    catch (IOException ex) { }
   	 	                    BTArrayAdapter.clear();
   	 	                    BTArrayAdapter.notifyDataSetChanged();
	        		    }   
	           		    else {
	        		      text.setText ( "Bad " + device.getName() + " not " + name + ".");
	        		    }
	        		 } 
	        		 else
	        			 text.setText ( "index == 0 for " + chosenOne );
	        	 }	 

	        }
	    }
	};
	
   public void find(View view) {
	   if (myBluetoothAdapter.isDiscovering()) {
		   // the button is pressed when it discovers, so cancel the discovery
		   myBluetoothAdapter.cancelDiscovery();
 		   text.setText ( "Discovery Cancelled");
		   
	   }
	   else {
			BTArrayAdapter.clear();
			myBluetoothAdapter.startDiscovery();
  		    text.setText ( "Start Discovery");
			registerReceiver(bReceiver, new IntentFilter(BluetoothDevice.ACTION_FOUND));	
		}    
   }
   
   public void off(View view){
	  myBluetoothAdapter.disable();
	  text.setText("Status: Disconnected");
	  
      Toast.makeText(getApplicationContext(),"Bluetooth turned off",
    		  Toast.LENGTH_LONG).show();
   }
   
   @Override
   protected void onDestroy() {
	   // TODO Auto-generated method stub
	   super.onDestroy();
	   unregisterReceiver(bReceiver);
   }
   
   void openBT() throws IOException
   {
       UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
       mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);        
       mmSocket.connect();
       mmOutputStream = mmSocket.getOutputStream();
       mmInputStream  = mmSocket.getInputStream();
       
       //String msg = myTextbox.getText().toString();
       //msg += "\n";
       String msg = "Hello from Android\n";
       mmOutputStream.write(msg.getBytes());
       text.setText("Data Sent");
       
       beginListenForData();       
       // text.setText("Bluetooth Opened");
   }

   
   void beginListenForData()
   {
       final Handler handler = new Handler(); 
       final byte delimiter = 10; //This is the ASCII code for a newline character
       
       stopWorker = false;
       readBufferPosition = 0;
       readBuffer = new byte[1024];
       workerThread = new Thread(new Runnable()
       {
           public void run()
           {                
              while(!Thread.currentThread().isInterrupted() && !stopWorker)
              {
                   try 
                   {
                       int bytesAvailable = mmInputStream.available();                        
                       if(bytesAvailable > 0)
                       {
                           byte[] packetBytes = new byte[bytesAvailable];
                           mmInputStream.read(packetBytes);
                           for(int i=0;i<bytesAvailable;i++)
                           {
                               byte b = packetBytes[i];
                               if(b == delimiter)
                               {
                                   byte[] encodedBytes = new byte[readBufferPosition];
                                   System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                   final String data = new String(encodedBytes, "US-ASCII");
                                   readBufferPosition = 0;
                                   
                                   handler.post(new Runnable()
                                   {
                                       public void run()
                                       {
                                           text.setText(data);
                                       }
                                   });
                               }
                               else
                               {
                                   readBuffer[readBufferPosition++] = b;
                               }
                           }
                       }
                   } 
                   catch (IOException ex) 
                   {
                       stopWorker = true;
                   }
              }
           }
       });

       workerThread.start();
   }
   
		
}
