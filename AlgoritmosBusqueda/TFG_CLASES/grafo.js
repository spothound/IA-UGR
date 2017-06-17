


class Grafo{
	constructor(container_id){
		this.node_ids=[];
		this.node_heuristics=[];
		this.initial_node_id=null;
		this.end_nodes_id=[];


		this.edge_data=[];
		
		this.vis_nodes = new vis.DataSet();
	    this.vis_edges = new vis.DataSet();

	    
	    this.numNodes=0;
	    this.numEdges=0;

		var container = document.getElementById(container_id);
		var data = {
			nodes: this.vis_nodes,
			edges: this.vis_edges
		};
		var options = {};

		this.grafo = new vis.Network(container, data, options);
		
		//this.algorithms= new Algorithms();

		//alert("Grafo construido");

		this.initialColor="red";
		this.endColor="green";
		this.selectedColor="yellow";
	}


	setContent_solution(container_id,network_step){
		try{
			this.numNodes=network_step.nodes.length;
			this.numEdges=network_step.edges.length;

			this.node_ids=new Array(this.numNodes);
			this.node_heuristics=new Array(this.numNodes);
			
			this.initial_node_id=null;
			this.end_nodes_id=[];

			this.vis_nodes = new vis.DataSet();


			//Meto los nodos del paso actual
		    for(var i=0;i<this.numNodes;i++){
		    	if(Object.keys(network_step.nodes[i]).length == 4){
			    	this.vis_nodes.add({
		                id: network_step.nodes[i].id,
		                label: network_step.nodes[i].label,
		                title: parseInt(network_step.nodes[i].title), //Heuristica del nodo
		                color: network_step.nodes[i].color
		            });
	        	}else{
	        		this.vis_nodes.add({
		                id: network_step.nodes[i].id,
		                label: network_step.nodes[i].label,
		                title: parseInt(network_step.nodes[i].title), //Heuristica del nodo
		            	color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
		            });
	        	}

	        	this.node_ids[i]=network_step.nodes[i].id;
				this.node_heuristics[i]=parseInt(network_step.nodes[i].title);


	        	if(network_step.nodes[i].color==this.initialColor){
	        		this.initial_node_id=network_step.nodes[i].id;
	        	}else if(network_step.nodes[i].color==this.endColor){
	        		this.end_nodes_id.push(network_step.nodes[i].id);
	        	}
		    }


		    
		    //Meto los edges del paso actual
		    this.edge_data=new Array(this.numEdges);
		    this.vis_edges = new vis.DataSet();
		    for(var i=0;i<this.numEdges;i++){
		    	if(Object.keys(network_step.edges[i]).length == 5){//Nodo con atributo arrows
		    		this.vis_edges.add({
		                from: network_step.edges[i].from,
		                to: network_step.edges[i].to,
		                id: network_step.edges[i].id,
		                label: network_step.edges[i].label,
		                arrows: network_step.edges[i].arrows
		            });
		    		this.edge_data.push([network_step.edges[i].from,network_step.edges[i].to,parseInt(network_step.edges[i].label),true]);
		    	}else{ //Nodo sin atributo color
		    		this.vis_edges.add({
		                from: network_step.edges[i].from,
		                to: network_step.edges[i].to,
		                id: network_step.edges[i].id,
		                label: network_step.edges[i].label
		            });
		            this.edge_data.push([network_step.edges[i].from,network_step.edges[i].to,parseInt(network_step.edges[i].label),false]);
		    	}

		    }
		    
		    
			var container = document.getElementById(container_id);
			var data = {
				nodes: this.vis_nodes,
				edges: this.vis_edges
			};
			var options = {};

			this.grafo = new vis.Network(container, data, options);


		}catch(err){alert(err);}
		
		//this.algorithms= new Algorithms();

		//alert("Grafo construido por network_step");
	}






	setContent(_container_id,_vis_nodes,_vis_edges,_node_heuristics,_initial_node_id,_end_nodes_id){ //Sobrecargado
		//Introduzco datos de los nodos
		this.node_ids=[];//
		this.node_heuristics=[];//
		this.initial_node_id=null;//
		this.end_nodes_id=[];//
		this.numNodes=0;

		var nodes = _vis_nodes.get({
						  fields: ['id'],
						});
						
		for(var i=0;i<nodes.length;i++){
			this.node_ids.push(nodes[i].id);
			this.numNodes+=1;
		}

		this.node_heuristics=_node_heuristics;
		this.initial_node_id=_initial_node_id;
		this.end_nodes_id=_end_nodes_id;

		//Introduzco los datos de las aristas
		this.edge_data=[];
	    this.numEdges=0;

	    var edges = _vis_edges.get({
						  fields: ['id','from','to','label','arrows'],    // output the specified fields only
						});
		var reg;			
		for(var i=0;i<edges.length;i++){
			if(edges[i].arrows=="to"){
				reg=[edges[i].from,edges[i].to,parseInt(edges[i].label),true];
			}else{
				reg=[edges[i].from,edges[i].to,parseInt(edges[i].label),false];
			}
			this.edge_data.push(reg);
			this.numEdges+=1;
		}


	    this.vis_nodes = _vis_nodes;
	    this.vis_edges = _vis_edges;
		var container = document.getElementById(_container_id);
		var data = {
			nodes: this.vis_nodes,
			edges: this.vis_edges
		};
		var options = {};

		this.grafo = new vis.Network(container, data, options);

		this.initialColor="red";
		this.endColor="green";
		this.selectedColor="yellow";
	}








































	getNetwork(){return this.grafo;}
	getNodes(){return this.vis_nodes;}
	getEdges(){return this.vis_edges;}


	getDescription(){
		var network_description="Nodos: "+this.node_ids[0]
		for (var i=1;i<this.node_ids.length;i++){
			network_description=network_description+","+this.node_ids[i];
		}

		network_description=network_description+"\nHeuristicas: "+this.node_heuristics[0];
		for (var i=1;i<this.node_heuristics.length;i++){
			network_description=network_description+","+this.node_heuristics[i];
		}

		network_description=network_description+"\nAristas:\n";
		for (var i=0;i<this.numEdges;i++){
			if(this.edge_data[i][3]){ //Arista dirigida
				network_description=network_description+" de "+this.edge_data[i][0]+" a "+this.edge_data[i][1]+" dirigida con coste "+this.edge_data[i][2]+"\n";
			}else{ //Arista bidireccional
				network_description=network_description+" de "+this.edge_data[i][0]+" a "+this.edge_data[i][1]+" bidireccional con coste "+this.edge_data[i][2]+"\n";
			}
		}

		network_description=network_description+"Nodo inicial: "+this.initial_node_id+".\n";
		network_description=network_description+"Nodo(s) final(es): "+this.end_nodes_id+".\n";

		return network_description;
	}




	//////////////////////////////////////////////////// METODOS DE NODOS ////////////////////////////////////////////////////



	initialNodeExists(){return this.initial_node_id!=null;}
	getInitialNodeId(){return this.initial_node_id;}
	getEndNodesId(){return this.end_nodes_id;}
	getNodeIds(){return this.node_ids;}
	getNodeHeuristics(){return this.node_heuristics;}
	getNumNodes(){return this.numNodes;}
	getInitialColor(){return this.initialColor;}
	getEndColor(){return this.endColor;}
	getSelectedColor(){return this.selectedColor;}

	setColorNodeInitial(node_id){
		this.vis_nodes.update({
			id: node_id,
			color: this.initialColor
    	});
	}

	setColorNodeEnd(node_id){
		this.vis_nodes.update({
			id: node_id,
			color: this.endColor
    	});
	}

	setColorNodeStandard(node_id){
		this.vis_nodes.update({
			id: node_id,
			color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
    	});
	}

	setColorNodeSelected(node_id){
		this.vis_nodes.update({
			id: node_id,
			color: this.selectedColor
    	});
	}

	//Agregar un nodo
	addNode(node_id,heur,is_initial,is_end){
		if(is_initial && !is_end){ //Se quiere poner como inicial
			this.vis_nodes.add({
				id: node_id,
				label: node_id+"\n(H="+heur+")",
				title: heur,
				color: "red"
			});
			this.initial_node_id=node_id;
		}else if(is_end && !is_initial){//Se quiere poner como final
			this.vis_nodes.add({
				id: node_id,
				label: node_id+"\n(H="+heur+")",
				title: heur,
				color: "green"
			});
			this.end_nodes_id.push(node_id);
		}else if(!is_initial && !is_end){ //Es un nodo intermedio
			this.vis_nodes.add({
				id: node_id,
				label: node_id+"\n(H="+heur+")",
				title: heur,
				color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
			});
		}else{
			return -1; //Codigo de error -1 me dice que se quiere poner un nodo como inicial y final
		}
    	this.node_ids.push(node_id);
		this.node_heuristics.push(heur);
		this.numNodes+=1;

		return 1; //El codigo 1 me indica que todo se realizo correctamente
	}




	updateNode(node_id,heur,is_initial,is_end) {
		//Comprobar que existe el nodo:
		var index_node=this.node_ids.indexOf(node_id);
		if(index_node != -1){ //El nodo existe
			if(is_initial && !is_end){ //Se quiere poner como inicial
				//Pongo el que estaba como inicial a intermedio
				if(this.initial_node_id!=null){
					this.vis_nodes.update({
						id: this.initial_node_id,
						label: this.initial_node_id+"\n(H="+heur+")",
						title: heur,
						color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
			    	});
		    	}
		    	//Coloco como nuevo nodo inicial el nodo que me han dicho
				this.vis_nodes.update({
					id: node_id,
					label: node_id+"\n(H="+heur+")",
					title: heur,
					color: "red"
		    	});
		    	//El nuevo nodo inicial es el que me han dicho
		    	this.initial_node_id=node_id;
			}else if(is_end && !is_initial){//Se quiere poner como final
				if(!this.end_nodes_id.includes(node_id)){
					this.end_nodes_id.push(node_id);
            	}
				this.vis_nodes.update({
		        	id: node_id,
		        	label: node_id+"\n(H="+heur+")",
		            title: heur,
		        	color: "green"
		    	});
			}else if(!is_initial && !is_end){ //Es un nodo intermedio
				this.vis_nodes.update({
		        	id: node_id,
		        	label: node_id+"\n(H="+heur+")",
		            title: heur,
		        	color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
		    	});

				//El nodo se va a convertir en intermedio, tengo que quitarlo de finales si era un nodo final
				var index_in_finals=this.end_nodes_id.indexOf(node_id);
            	if(index_in_finals!=-1){
            		this.end_nodes_id.splice(index_in_finals,1); //Eliminar el nodo del array de nodos finales si era final
            	}
            	
            	//El nodo se va a convertir en intermedio, tengo que quitarlo de inicial si era el nodo inicial
            	if(node_id==this.initial_node_id){
            		this.initial_node_id=null;
            	}

			}else{
				return -2; //Codigo de error -2 me dice que se quiere poner un nodo como inicial y final
			}
    	}else{
    		return -1; //Codigo de error -1 me dice que se quiere actualizar un nodo que no existe
    	}
    	this.node_heuristics[index_node]=heur;
	    return 1; //El codigo 1 me indica que todo se realizo correctamente
	}



	removeNode(node_id){
		try {
			if(this.node_ids.indexOf(node_id)!=-1){
				this.vis_nodes.remove({id: node_id});
				this.numNodes-=1;
				
				if(node_id == this.initial_node_id){ //He borrado el nodo inicial
					this.initial_node_id=null;
		        }

				var index_in_finals=this.end_nodes_id.indexOf(node_id);
				if(index_in_finals!=-1){
					this.end_nodes_id.splice(index_in_finals,1); //Eliminar el nodo del array de nodos finales si era final
				}

				var index_in_node_ids=this.node_ids.indexOf(node_id);
				if(index_in_node_ids!=-1){
					this.node_ids.splice(index_in_node_ids,1);
					this.node_heuristics.splice(index_in_node_ids,1);
				}

				//Elimino también todos los edges asociados al nodo
				var edge_id="";
				var edges_to_remove=[];
				for (var i=0;i<this.numEdges;i++){
					if(this.edge_data[i][0]==node_id || this.edge_data[i][1]==node_id){
						if(this.edge_data[i][3]){ //Si es una arista dirigida
							edge_id=this.edge_data[i][0]+"_"+this.edge_data[i][1]+"_"+"directed";
						}else{//Si es una arista normal
							edge_id=this.edge_data[i][0]+"_"+this.edge_data[i][1]+"_"+"normal";
						}
						this.vis_edges.remove({id: edge_id});
						edges_to_remove.push(this.edge_data[i]);
					}
				}

				for (var i=0; i<edges_to_remove.length;i++){
					//alert("Eliminar: "+edges_to_remove[i]);
					this.edge_data.splice(this.edge_data.indexOf(edges_to_remove[i]),1);
					this.numEdges-=1;
				}

			}
	    }catch (err) {
	        alert(err);
	    }
	    
	}


	

	////////////////////////////////////////////////// FIN METODOS DE NODOS //////////////////////////////////////////////////

	/////////////////////////////////////////////////// METODOS DE ARISTAS ///////////////////////////////////////////////////

	getEdgeIds(){
		edge_ids=new Array(this.numEdges);
		for(var i=0;i<this.numEdges.length;i++){
			if(this.edge_data[i][3]){//Arista dirigida
				edge_ids[i]=this.edge_data[i][0]+"_"+this.edge_data[i][1]+"_directed";
			}else{
				edge_ids[i]=this.edge_data[i][0]+"_"+this.edge_data[i][1]+"_normal";
			}
		}
		return edge_ids;
	}

	getEdgeData(){
		return this.edge_data;
	}

	getNumEdges(){return this.numEdges;}




	addEdge(node_from,node_to,cost,directed) {
		var new_edge_id=""
		
		if(directed){//Vamos a insertar una arista dirigida
			new_edge_id=node_from+"_"+node_to+"_directed";
	    }else{ //Vamos a insertar una arista bidireccional
			new_edge_id=node_from+"_"+node_to+"_normal";
	    }

	    for (var i=0;i<this.numEdges;i++){
	    	if(this.edge_data[i][0]==node_from && this.edge_data[i][1]==node_to){
	        	return -1; //El código de error -1 me dice que ya existe una arista entre esos dos nodos
	        }
	    }

        //alert("Se mete con la id: "+new_edge_id);
        try {
        	if(this.node_ids.indexOf(node_from)!=-1 && this.node_ids.indexOf(node_to)!=-1){ //Si ambos nodos existen en el grafo
        		if(directed){ //Si es arista dirigida
        			this.vis_edges.add({
	                    from: node_from,
	                    to: node_to,
	                    id: new_edge_id,
	                    label: cost,
	                    arrows: "to"
                	});
        		}else{
	                this.vis_edges.add({ //Si es arista bidireccional
	                    from: node_from,
	                    to: node_to,
                        id: new_edge_id,
	                    label: cost
	                });
                }
                this.edge_data.push([node_from,node_to,cost,directed]);
                //alert([node_from,node_to,cost,directed].toSource());
                this.numEdges+=1;
            }else{
            	return -2; //El código de error -2 me dice que uno de los dos no existe
            }
        }
        catch (err) {
            alert(err);
        }

        return 1; //El codigo 1 me indica que todo se realizo correctamente

	}









	updateEdge(node_from,node_to,cost,directed){
		var correct_id=null;
		var edge_index=-1;
		
		var was_directed=false;

		for(var i=0;i<this.numEdges;i++){
			if(this.edge_data[i][0] == node_from && this.edge_data[i][1] == node_to){
				if(this.edge_data[i][3]){//Arista dirigida
					correct_id=node_from+"_"+node_to+"_directed";
					was_directed=true;
				}else{//Arista bidireccional
					correct_id=node_from+"_"+node_to+"_normal";
					was_directed=false;
				}
				edge_index=i;
				break;
			}
		}

		if(correct_id!=null){
			try {
				if(directed && !was_directed){ //Era normal y la quiere dirigida
					this.vis_edges.remove({id: correct_id});
					this.vis_edges.add({
						from: node_from,
						to: node_to,
						id: node_from+"_"+node_to+"_directed",
						label: cost,
						arrows: "to"
					});
				}else if(!directed && was_directed){ //Era dirigida y la quiere normal
					this.vis_edges.remove({id: correct_id});
					this.vis_edges.add({
						from: node_from,
						to: node_to,
						id: node_from+"_"+node_to+"_normal",
						label: cost
	            	});
	        	}else{ //Es normal y la quiere normal o es dirigida y la quiere dirigida, lo unico que quiere es cambiar el coste
	        		this.vis_edges.update({
	                    id: correct_id,
	                    label: cost,
	            	});
	        	}

	        }
	        catch (err) {
	            alert(err);
	        }
	    }else{
	    	return -1; //El código de error -1 me dice que la arista que se quiere actualizar no existe
	    }
	    this.edge_data[edge_index]=[node_from,node_to,cost,directed];
	    return 1; //El codigo 1 me indica que todo se realizo correctamente
	}




	removeEdge(node_from,node_to) {
		try {
			for (var i=0;i<this.numEdges;i++){
				if(this.edge_data[i][0]==node_from && this.edge_data[i][1]==node_to){
					if(this.edge_data[i][3]){
						this.vis_edges.remove({id: node_from+"_"+node_to+"_directed"});	
					}else{
						this.vis_edges.remove({id: node_from+"_"+node_to+"_normal"});
					}
					this.edge_data.splice(i,1); //Eliminar el arco del array de nodos finales si era final
					this.numEdges-=1;
					break;
				}else if(this.edge_data[i][1]==node_from && this.edge_data[i][0]==node_to){
					if(!this.edge_data[i][3]){
						this.vis_edges.remove({id: node_from+"_"+node_to+"_normal"});	
					}
					this.edge_data.splice(i,1);
					this.numEdges-=1;
					break;
				}
			}
		}
		catch (err) {
			alert(err);
		}
	}





	updateHeuristics(node_ids,new_heuristics){
		try {
	    	if(new_heuristics.length==this.numNodes){
	    		for(var i=0;i<node_ids.length;i++){
	    			this.vis_nodes.update({
	    				id:node_ids[i],
	    				title:new_heuristics[i],
	    				label: node_ids[i]+"\n(H="+new_heuristics[i]+")",
	    			});
	    		}
	    		this.node_heuristics=new_heuristics;
	    	}else{
	    		return -1; //El codigo de error -1 me indica que no puede aplicarse la heuristica porque el numero de valores heuristicos no coincide con el numero de nodos
	    	}
	    
	    }catch (err) {
	    	alert(err);
	    }
	    return 1;
	}

	///////////////////////////////////////////////// FIN METODOS DE ARISTAS /////////////////////////////////////////////////

}