// JavaScript for WORD Data Lookup Demo
// Jensen Shurbert, Kenyon College, 2017


$(document).ready(function () {
    console.log("start!");
    //searchType="Last";
    $("#search-btn").click(getMatches);

    $("#clear").click(clearResults);

});


function processResults(results) {
	//console.log("results:"+results);
    $('#searchresults').empty();
    $('#searchresults').append(results);
}

function clearResults() {
    $('#searchresults').empty();
}

//sends searched word to the index, sends out results or error message
function getMatches(){
    if ($('#search').val().length < 2) return;
    $('#searchresults').empty();
    $.ajax({
		url: '/cgi-bin/shurbertj_wordlookupclient.cgi?shake='+$('#search').val(),
		dataType: 'text',
		success: processResults,
		error: function(){alert("Error: Something went wrong");}
    });

}
