/**
* Responsible for initializing the js code.
*/
function init(){

	/**
	* Holds the id of what will be updated.
	*/
	var updateId = "#problem1Rate";

	/**
	* Holds the multiplication factor.
	*/
	var offset = 1.0;

	/**
	* Holds the problem number.
	*/
	var problemNumber = "problem1";

	/**
	* Holds the graph being used..
	*/
	var graph;

	/**
	* Holds the chart svg.
	*/
	var svg;
			
	/**
	* Entry point...
	*/
	start = function(selection){
		$(function(){
			selection.slider({
				min:1,
				max:9,
				values:[1],	
				step:1,				
				stop: function(event,ui){
					$(updateId).val(Math.round(offset*selection.slider("values",0)
					*100)/100);
					if(offset==.05){
						if(problemNumber=="problem1"){
							p1LearningRate = selection.slider("values",0);	
						}else if(problemNumber=="problem2"){
							p2LearningRate = selection.slider("values",0);
						}	
					}else{
						if(problemNumber=="problem1"){
							p1HiddenLayers = selection.slider("values",0);	
						}else if(problemNumber=="problem2"){
							p2HiddenLayers = selection.slider("values",0);
						}	
					}
					d3.csv(problemNumber+"/test/"+p1LearningRate+"_"+p1HiddenLayers
					+".txt",function(error,data){
							if(error){
								console.log("Could not load the data");
								return;
							}
							console.log(data);	
					});	
				}
			});
		$(updateId).val(Math.round(offset*selection.slider("values",0)
			*100)/100);	
		});
	}
	

	/**
	* Getter/Setter for the updateId.
	*/
	start.updateId = function(_){
		if(!arguments.length) return updateId;
		updateId = _;
		return start;
	}

	/**
	* Getter/Setter for the offset.
	*/
	start.offset = function(_){
		if(!arguments.length) return offset;
		offset = _;
		return start;
	}

	/**
	* Getter/Setter for the problem number.
	*/	
	start.problemNumber = function(_){
		if(!arguments.length) return problemNumber;
		problemNumber=_;
		return start;
	}

	/**
	* Getter/Setter for the graph.
	*/
	start.graph = function(_){
		if(!arguments.length) return graph;
		graph = _;
		return start;
	}

	/**
	* Getter/Setter for the svg for the graph
	*/
	start.svg = function(_){
		if(!arguments.length) return svg;
		svg = _;
		return start;
	}

	return start;
}

function LineGraph(){

	var width;
	var height;
	var svg;
	var margins={marginTop:10,marginBottom:10,marginLeft:10,marginRight:10};

	chart = function(selection){
		selection.each(function(data){	
			if(!svg){
				drawingHeight = height - margins.marginTop - margins.marginBottom;	
				drawingWidth = width - margins.marginLeft - margins.marginRight;
				console.log(data);							
			}else{

			}
		});
	}

	chart.width = function(_){
		if(!arguments.length) return width;
		width = _;
		return chart;
	}

	chart.height = function(_){
		if(!arguments.length) return height;
		height = _;
		return chart;
	}
	return chart;
}
