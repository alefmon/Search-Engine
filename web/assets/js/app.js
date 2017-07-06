//Check off specific todos by clicking
$("ul").on("click", "li", function(){ //When an li is clicked inside an ul.
	$(this).toggleClass("done");
});

//Remove todo by clicking on delete icon
$("ul").on("click", "span", function(event){
	event.stopPropagation();
	$(this).parent().fadeOut(function(){
		$(this).remove();
	});
});

$("input[type='text']").on("keypress", function(event){
	if(event.which === 13){
		//Grabbing new todo text from input
		var todoText = $(this).val();
		//Create a new li and add to ul
		$("ul").append("<li>" + "<span><i class='fa fa-trash' aria-hidden='true'></i></span> " + todoText + "</li>");
		//Clear input
		$(this).val("");
	}
});

$(".fa-plus").on("click", function(){
	$("input").fadeToggle("fast"); 
});
