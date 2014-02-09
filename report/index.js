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
	* Holds the max value.
	*/
	var max=10;
			
	/**
	* Entry point...
	*/
	start = function(selection){
		$(function(){
			selection.slider({
				min:1,
				max:max,
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
						d3.select(svg)
							.datum(data)
							.call(graph);
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

	/**
	* Getter/Setter for the max.
	*/
	start.max = function(_){
		if(!arguments.length) return max;
		max = _;
		return start;
	}

	return start;
}

function LineGraph(){

	var width;
	var height;
	var svg;
	var margins={marginTop:30,marginBottom:30,marginLeft:100,marginRight:30};
	var xScale = d3.scale.linear();
	var yScale = d3.scale.linear();
	var xAxis = d3.svg.axis();
	var yAxis = d3.svg.axis();

	chart = function(selection){
		selection.each(function(data){
			drawingHeight = height - margins.marginTop - margins.marginBottom;	
			drawingWidth = width - margins.marginLeft - margins.marginRight;
			console.log("here");	
			xScale.domain([0,5000]);
			xScale.range([margins.marginLeft,drawingWidth]);
			range = d3.extent(data,function(d){
				return d.RMSE;	
			});
			yScale.range([drawingHeight,margins.marginTop]);
			yScale.domain([0,.33]);
			xAxis.scale(xScale)	
				.orient("bottom");
			yAxis.scale(yScale)	
				.orient("left");
			line = d3.svg.line()
				.x(function(d){return xScale(d.epochNumber);})
				.y(function(d){return yScale(d.RMSE);});
							
			if(!svg){
				svg = d3.select(this).append("svg")
					.attr("width",width)
					.attr("height",height)
					.attr("transform","translate("+margins.marginLeft+","+
						margins.marginTop+")");	

				svg.append("path")
					.datum(data)
					.attr("class","line")
					.attr("d",line);

				svg.append("g")
					.attr("class","x axis")
					.attr("transform","translate(0,"+drawingHeight+")")
					.call(xAxis);	
				
				svg.append("g")
					.attr("class","y axis")
					.attr("transform","translate("+margins.marginLeft+",0)")	
					.call(yAxis);	

			}else{		
				svg.selectAll(".line")
					.datum(data)
					.transition()
					.duration(500)
					.attr("class","line")
					.attr("d",line);	

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
