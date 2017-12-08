var reloadSnapshot = function(){
  d = new Date();
  $("#snapshot").attr("src", "snapshot.jpg?" + d.getTime());
};

var points = [];

$(document).ready(function(){
  setInterval(reloadSnapshot, 500);

  $('#calibrateBtn').click(function(event){
    $.ajax({
      url: '/php/calibrate.php',
      type: 'GET',

      success: function(msg){
        console.log(msg);
        $('#calibrateBtn').addClass('hidden');
        $('#cancelBtn').removeClass('hidden');
        $('#snapshot').removeClass('hidden');
      },

      error: function(){
        alert('Calibrate gateway not available');
      }
    }); // ajax
  }); // #calibrateBtn click

  $('#cancelBtn').click(function(event){
    $.ajax({
      url: '/php/cancel.php',
      type: 'GET',

      success: function(msg){
        console.log(msg);
        $('#cancelBtn').addClass('hidden');
        $('#calibrateBtn').removeClass('hidden');
        $('#snapshot').addClass('hidden');
      },

      error: function(){
        alert('Cancel gateway not available');
      }
    }); // ajax
  }); // #cancelBtn click

  $('#snapshot').click(function(event){
    var elm = $(this);
    var xPos = event.pageX - elm.offset().left;
    var yPos = event.pageY - elm.offset().top;

    console.log(xPos, yPos);

    $.ajax({
      url: '/php/point.php',
      type: 'POST',
      data: {x:xPos, y:yPos},

      success: function(msg){
        console.log(msg);

        if(points.length >= 4){
          points = [];
          $('#cancelBtn').addClass('hidden');
          $('#calibrateBtn').removeClass('hidden');
          $('#snapshot').addClass('hidden');
        }else{
          points.push({x: xPos, y:yPos});
        }
      },

      error: function(){
        alert('Point gateway not available');
      }
    }); // ajax
  });
});
