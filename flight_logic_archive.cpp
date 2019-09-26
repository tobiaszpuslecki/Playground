
//state boot{

  uint8_t transmissionFrequency = 1;
  uint8_t samplingFrequency = 1;
  uint8_t configCycle = 4;

  while(configCycle--)
  {
      config();
      if (config.OK())
      {
        break;
      }
      else
      {
        //debug information about errors
        //working without less important periph
      }
  }

  packetCounter = read.lastPacketCounter;
  refPressure = read.lastRefPressure;
  refPitch = read.lastRefPitch;
  refRoll = read.lastRefRoll;
  swState = read.lastSwState;

  return sw_state;
}

//state prelaunch{

  sw_state = PRELAUNCH_STATE;

  uint8_t calibCycle = 4;

  while(calibCycle--)
  {
    calibration();
    if(calibration.OK())
      break;
    else
      //debug information about errors

  }
  return ready;
}

//state ready{
  sw_state = READY_STATE;

  bool REFERENCE_COMPLETE=false;
  bool RADIO_SIGNAL_RECIEVED=false;
  // radio interrupt check the code of signal, and if it's proper, set RADIO_SIGNAL_RECIEVED flag
  if (!REFERENCE_COMPLETE && RADIO_SIGNAL_RECIEVED)
  {
    refPressure = barometer.getPressure();
    refPitch = accelerometer.getPitch();
    refRoll = accelerometer.getRoll();

    samplingFrequency = 10;
    REFERENCE_COMPLETE=true;
  }
  else
  {
    // gather data from all sensors -> struct data ready to save or convert to string
    packetCounter++;
    SD.write(data);
    transmissionString = prepareString(data);
    Radio.send(transmissionString);
  }

  LAUNCH_DETECTED = (reglin(last_accelerations[]) > launchCoefficient) ? 1 : 0;

  if(REFERENCE_COMPLETE && LAUNCH_DETECTED)
  {
    return flightup;
  }

}

//state flightup{
    sw_state = FLIGHTUP_STATE;
    // gather data from all sensors -> struct data ready to save or convert to string
    packetCounter++;
    SD.write(data);
    transmissionString = prepareString(data);
    Radio.send(transmissionString);


    HIGHEST_POINT = (reglin(last_accelerations[]) < descendingCoefficient) ? 1 : 0;

    if(HIGHEST_POINT && calculateAltitude(barometer.getPressure()) <= 450) // CanSat descends and altitide reached
    {
      return container;
    }

}

//state container{
  sw_state = CONTAINER_STATE;
  // gather data from all sensors -> struct data ready to save or convert to string
  packetCounter++;
  SD.write(data);
  transmissionString = prepareString(data);
  Radio.send(transmissionString);






  if ( hall.getRotationSpeed() > 0 )
  {
    return autogyro;
  }
  if (calculateAltitude(barometer.getPressure()) <= BREAKING_LVL)
  {
    return breaking;
  }

}

//state autogyro{
  sw_state = AUTOGYRO_STATE;
  // gather data from all sensors -> struct data ready to save or convert to string
  packetCounter++;
  SD.write(data);
  transmissionString = prepareString(data);
  Radio.send(transmissionString);

  servo.set(calculateAngle());




  if (calculateAltitude(barometer.getPressure()) <= BREAKING_LVL)
  {
    return breaking;
  }

}

//state breaking{
  sw_state = BREAKING_STATE;
  servo.set(MAX);


  // gather data from all sensors -> struct data ready to save or convert to string
  packetCounter++;
  SD.write(data);
  transmissionString = prepareString(data);
  Radio.send(transmissionString);

  CONSTANT_ACCELERATION = (reglin(last_accelerations[]) ~ 0) ? 1 : 0; // reglin result near zero

  if (CONSTANT_ACCELERATION)
  {
    return touchdown;
  }
}

//state touchdown{
  sw_state = TOUCHDOWN_STATE;

  // all calculation/sensors etc STOP

  radio.stopTransmission()
  audiobeacon.active()

  // Mission complete
}
