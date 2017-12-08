var reloadSnapshot = function(){
  d = new Date();
  $("#snapshot").attr("src", "snapshot.jpg?" + d.getTime());
};

$(document).ready(function(){
  setInterval(reloadSnapshot, 500);

  $('#calibrateBtn').click(function(event){
    // Send OSC message to the app and check for response
    // Address: /calibrate

    $(this).addClass('hidden');
    $('#confirmBtn').removeClass('hidden');
    $('#cancelBtn').removeClass('hidden');
    $('#snapshot').removeClass('hidden');
  });

  $('#confirmBtn').click(function(event){
    // Send coordinate data to app via osc
    // Address: /confirm

    $(this).addClass('hidden');
    $('#cancelBtn').addClass('hidden');
    $('#calibrateBtn').removeClass('hidden');
    $('#snapshot').addClass('hidden');
  });

  $('#cancelBtn').click(function(event){
    // Send OSC message to the app and check for response
    // Address: /cancel

    $(this).addClass('hidden');
    $('#confirmBtn').addClass('hidden');
    $('#calibrateBtn').removeClass('hidden');
    $('#snapshot').addClass('hidden');
  });

  $(document).keypress(function(event){
    console.log('Key has been pressed: ' + event.which);
    
    if(event.which == 99){
      alert('Entering calibration mode. Press <q> to exit.');
    } else if (event.which == 113) {
      // exit calib mode
    }

  });
});

/*
$('#shutdown-button').click(function(){
  $.ajax({
    url: '/php/shutdown.php',
    type: 'POST',

    success: function(msg){
      console.log(msg);
      alert('System shuttnig down');
    },

    error: function(){
      alert('Shutdown script not available');
    }
  });
});
*/
