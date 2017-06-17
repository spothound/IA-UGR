class Interface_Handler{
	constructor(){
		this.grafo_principal=new Grafo("network");
		this.grafo_solucion=new Grafo("solution_network");
		
		try{
			this.algorithms=new Algorithms();
		}catch(err){alert(err);}

		this.is_initial_selected=false;
		this.initialization();

		this.imported_nodes;
		this.imported_edges;
		this.imported_initial_node;
		this.imported_end_nodes;

		this.created_events=false;

		this.index_step=0;

		this.resolution;
	}
	

	addNode(){
	    /*Estructura de los nodos:
	        id: identificador del nodo
	        label: lo que aparece en pantalla, el id del nodo junto con su función heurística
	        color: color del nodo
	        title: en este apartado guardaremos la heuristica
	    */
	    var node_id=document.getElementById('node-id').value;
		if(node_id==""){
			alert("El id del nodo no puede estar vacio");
		}else{
	        try {
	            var heur=parseInt(document.getElementById('node-heuristic').value);
	            
	            if(!isNaN(heur)){
	            	if(heur>=0){
			            if(document.getElementById('cb_initial_node').checked && !document.getElementById('cb_final_node').checked){ //Si es nodo inicial
			            	if(!this.grafo_principal.initialNodeExists()){
			            		this.grafo_principal.addNode(node_id,heur,true,false);
			                	document.getElementById('cb_initial_node').checked=false;
			                	document.getElementById('cb_initial_node').disabled=true;
			            	}else{
			            		alert("El nodo inicial ya está definido. Si el checkbox de nodo inicial esta activado es porque tiene el nodo inicial seleccionado. Desactivelo pinchando en un nodo intermedio o en cualquier zona del grafo donde no haya nodo");
			            	}
			            }else if(!document.getElementById('cb_initial_node').checked && document.getElementById('cb_final_node').checked){//Se quiere poner como final
			            	this.grafo_principal.addNode(node_id,heur,false,true);
			            }else if(document.getElementById('cb_initial_node').checked && document.getElementById('cb_final_node').checked){
			            	alert("Un nodo no puede ser inicial y final a la vez");     
			            }else{
			            	this.grafo_principal.addNode(node_id,heur,false,false);
			            }
			            this.resetNodeEntry();
			            if(!this.created_events){
			            	this.createNetworkEvents();
			            	$("#submenu").fadeIn("slow");
			            }
			            this.printInfo();
			        }else{
			        	alert("Por favor, introduzca un valor heurístico estrictamente positivo.");
			        }
		        }else{
		        	alert("Por favor, introduzca un valor entero en el campo Valor heurístico.");
		        }

	        }
	        catch (err) {
	            alert(err);
	        }



	        if(this.grafo_principal.initialNodeExists()){
	        	document.getElementById('cb_initial_node').disabled=true;
	        	document.getElementById('cb_initial_node').checked=false;
	        }else{
	        	document.getElementById('cb_initial_node').disabled=false;
	        	document.getElementById('cb_initial_node').checked=false;
	        }
	    }	   
	}
	



	updateNode(){
		/*Estructura de los nodos:
	        id: identificador del nodo
	        label: lo que aparece en pantalla, el id del nodo junto con su función heurística
	        color: color del nodo
	        title: en este apartado guardaremos la heuristica
	    */
	    var node_id=document.getElementById('node-id').value;
		if(node_id==""){
			alert("El id del nodo no puede estar vacio");
		}else{
	        try {
	            var heur=parseInt(document.getElementById('node-heuristic').value);
	            
	            if(!isNaN(heur)){
	            	if(heur>=0){
	            		var error=this.grafo_principal.updateNode(node_id,heur,document.getElementById('cb_initial_node').checked,document.getElementById('cb_final_node').checked);
	            		switch(error){
			            	case -2: alert("Un nodo no puede ser inicial y final a la vez");break;//Codigo de error -2 me dice que se quiere poner un nodo como inicial y final
							case -1: alert("El nodo que se esta intentando actualizar no existe.");break; //Codigo de error -1 me dice que se quiere actualizar un nodo que no existe
			           		default: 
			           			this.is_initial_selected=false;

					            this.resetNodeEntry();
					            if(!this.created_events){
					            	this.createNetworkEvents();
					            	$("#submenu").fadeIn("slow");
					            }
					            this.printInfo();
			           			break; 
			           }
	            	}else{
	            		alert("Por favor, introduzca un valor heurístico estrictamente positivo.");
	            	}
	            }else{
	            	alert("Por favor, introduzca un valor entero en el campo Valor heurístico.");
	            }

	            

	        }
	        catch (err) {
	            alert(err);
	        }



	        if(this.grafo_principal.initialNodeExists()){
	        	document.getElementById('cb_initial_node').disabled=true;
	        	document.getElementById('cb_initial_node').checked=false;
	        }else{
	        	document.getElementById('cb_initial_node').disabled=false;
	        	document.getElementById('cb_initial_node').checked=false;
	        }
	    }
	}


	removeNode(){
		try {
	    	var node_to_remove=document.getElementById('node-id').value;
	    	if(node_to_remove==""){
				alert("El id del nodo no puede estar vacio");
			}else{
		        //nodes.remove({id: node_to_remove});
		        if(this.grafo_principal.getNodeIds().includes(node_to_remove)){
			        
			        if(node_to_remove == this.grafo_principal.getInitialNodeId()){ //He borrado el nodo inicial
			        	document.getElementById('cb_initial_node').checked=false;
			        	document.getElementById('cb_initial_node').disabled=false;
			        	this.is_initial_selected=false;
			        }

			        this.grafo_principal.removeNode(node_to_remove);

					this.resetNodeEntry();

					if(!this.created_events){
			        	this.createNetworkEvents();
			        	$("#submenu").fadeIn("slow");
			        }
			        this.printInfo();
			    }else{
			    	alert("El nodo que intenta eliminar no existe.");
			    }
		    }

	    }
	    catch (err) {
	        alert(err);
	    }

	    if(this.grafo_principal.initialNodeExists()){
	    	document.getElementById('cb_initial_node').disabled=true;
	    	document.getElementById('cb_initial_node').checked=false;
	    }else{
	    	document.getElementById('cb_initial_node').disabled=false;
	    	document.getElementById('cb_initial_node').checked=false;
	    }

	}




	addEdge(){
		var src=document.getElementById('edge-from').value;
		var dst=document.getElementById('edge-to').value;
		var cost=parseInt(document.getElementById('edge-cost').value);

		if(!isNaN(cost)){
        	if(cost>=0){
        		var error=this.grafo_principal.addEdge(src,dst,cost,document.getElementById('cb_directed_edge').checked);
				switch(error){
					case -1: alert("Ya existe una arista entre estos dos nodos"); break;//El código de error -1 me dice que ya existe una arista entre esos dos nodos
					case -2: alert("Uno (o ambos) de los dos nodos ("+src+" o "+dst+") no existe.");break;//El código de error -2 me dice que uno de los dos no existe
					default: 
						this.is_initial_selected=false;
			            this.resetEdgeEntry();
			            if(!this.created_events){
			            	this.createNetworkEvents();
			            	$("#submenu").fadeIn("slow");
			            }
			            this.printInfo();
			            break;
				}		
        	}else{
        		alert("Por favor, introduzca un valor de coste estrictamente positivo.");
        	}
        }else{
        	alert("Por favor, introduzca un valor entero en el campo Coste.");
        }

		
	}

	updateEdge(){
		var src=document.getElementById('edge-from').value;
		var dst=document.getElementById('edge-to').value;
		var cost=parseInt(document.getElementById('edge-cost').value);

		if(!isNaN(cost)){
        	if(cost>=0){
        		var error=this.grafo_principal.updateEdge(src,dst,Number(cost),document.getElementById('cb_directed_edge').checked);

				switch(error){
					case -1: alert("La arista que se esta intentando actualizar no existe."); break;//El código de error -1 me dice que ya existe una arista entre esos dos nodos
					default: 
						this.is_initial_selected=false;
			            this.resetEdgeEntry();
			            if(!this.created_events){
			            	this.createNetworkEvents();
			            	$("#submenu").fadeIn("slow");
			            }
			            this.printInfo();
			            break;
				}
        	}else{
        		alert("Por favor, introduzca un valor de coste estrictamente positivo.");
        	}
        }else{
        	alert("Por favor, introduzca un valor entero en el campo Coste.");
        }



		
	}







	removeEdge(){
		var src=document.getElementById('edge-from').value;
		var dst=document.getElementById('edge-to').value;

		try{
			var edge_data=this.grafo_principal.getEdgeData();
			for(var i=0;i<edge_data.length;i++){
				if(edge_data[i][3]){//Arista dirigida
					if(edge_data[i][0]==src && edge_data[i][1]==dst){
						this.grafo_principal.removeEdge(src,dst);
						this.printInfo();
						return;
					}
				}else{//Arista bidireccional
					if((edge_data[i][0]==src && edge_data[i][1]==dst)){ 
						this.grafo_principal.removeEdge(src,dst);
						this.printInfo();
						return;
					}else if(edge_data[i][0]==dst && edge_data[i][1]==src){
						this.grafo_principal.removeEdge(dst,src);
						this.printInfo();
						return;
					}
				}		
			}
			alert("La arista que trata de eliminar no existe.");

		}catch(err){alert(err);}
		
	}





















	download(filename, text) {
	    var element = document.createElement('a');
	    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
	    element.setAttribute('download', filename);
	    element.style.display = 'none';
	    document.body.appendChild(element);
	    element.click();
	    document.body.removeChild(element);
	}


	exportNetwork(){
		try{
			if(this.is_initial_selected){
				alert("Por favor, seleccione el nuevo nodo inicial.");
			}else{
				if(!this.grafo_principal.initialNodeExists()){
			    	alert("Debe haber uno (y solo uno) nodo inicial");
			    }else if(this.grafo_principal.getEndNodesId().length==0){
			    	alert("Debe haber al menos un nodo final");
			    }else if(this.grafo_principal.getNumNodes()==0){
			        alert("No existen nodos finales.");
			    }else if(this.grafo_principal.getNumEdges()==0){
			        alert("No existen aristas.");
			    }else{
		            //Obtengo en string el codigo de los nodos y los edges
		            var code_nodes=this.grafo_principal.getNodes().get().toSource();
		            var code_edges=this.grafo_principal.getEdges().get().toSource();
		            var code_initial_node=this.grafo_principal.getInitialNodeId();
		            var code_end_nodes=this.grafo_principal.getEndNodesId().toSource();
		            this.download("grafo.txt",code_nodes+"*-*-*-*-*-*-*-*-*-*-"+code_edges+"*-*-*-*-*-*-*-*-*-*-"+code_initial_node+"*-*-*-*-*-*-*-*-*-*-"+code_end_nodes);
				}
			}
		}catch(err){
			alert(err);
		}
	}




	readSingleFile(evt) {
		var f = evt.target.files[0];
		if (f) {
			var r = new FileReader();
			r.onload = (function(e) {
				var contents = e.target.result;
				
				var result=contents.split("*-*-*-*-*-*-*-*-*-*-");
				this.imported_nodes=result[0];
				this.imported_edges=result[1];
				this.imported_initial_node=result[2];
				this.imported_end_nodes=result[3];

	            if(this.imported_nodes!=null && this.imported_edges!=null && this.imported_initial_node!=null && this.imported_end_nodes!=null){
	                $("#import-network-btn").prop("disabled",false);
	            }else{
	            	alert("El fichero no ha podido interpretarse");
	            }
			}).bind(this);
			r.readAsText(f);
		} else { 
			alert("Fallo al importar el archivo.");
		}
	}






	importNetwork(){
		try{
	    	var nodes = new vis.DataSet();
	        var edges = new vis.DataSet();
	        var node_heuristics=[];
	        var container = document.getElementById('network');



	        //---------------------------------INICIO IMPORTACION DE NODOS---------------------------------//
	        var string_nodes=this.imported_nodes.substr(1, this.imported_nodes.length-2).split("}, ");
	        var nnodes=string_nodes.length;
	        var node_color;
	        var potential_initial=null;
	        var potentials_end=[];
	        var potentials_nodes=[];

	        for(var i=0; i<nnodes; i++) {
	            if(i==nnodes-1){
	                string_nodes[i]=string_nodes[i].substr(1, string_nodes[i].length-2);    
	            }else{
	                string_nodes[i]=string_nodes[i].substr(1, string_nodes[i].length-1);
	            }


	            var splitted_by_comma=string_nodes[i].split(",");
	            var nfeatures=splitted_by_comma.length;
	            
	            if(nfeatures<=4){ //Caso general, nodo con color explicitamente
	            	string_nodes[i]=splitted_by_comma;
	            	

	                for(var j=0; j<string_nodes[i].length; j++) {
	                    string_nodes[i][j]=string_nodes[i][j].split(":")
	                }

	                if(string_nodes[i].length==4){ //Nodo que especifica el color
	                	if(string_nodes[i][3][1].substr(1,string_nodes[i][3][1].length-2)==this.grafo_principal.getInitialColor()){
	                		potential_initial=string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2); //Me quedo con el ID del supuesto inicial
	                		potentials_nodes.push(string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2));
	                	}else if(string_nodes[i][3][1].substr(1,string_nodes[i][3][1].length-2)==this.grafo_principal.getEndColor()){
	                		potentials_end.push(string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2));
	                		potentials_nodes.push(string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2));
	                	}
	                	nodes.add({
	                        id: string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2),
	                        label: string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2)+"\n(H="+string_nodes[i][2][1]+")",
	                        title: Number(string_nodes[i][2][1]), //Heuristica del nodo
	                        color: string_nodes[i][3][1].substr(1,string_nodes[i][3][1].length-2)
	                    });   
	                    node_heuristics.push(Number(string_nodes[i][2][1]));
	                    //alert("Nodos normales: \nID: "+string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2)+"\nLABEL: "+string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2)+"\n(H="+string_nodes[i][2][1]+")"+"\nHEURISTICA: "+Number(string_nodes[i][2][1])+"\nCOLOR"+string_nodes[i][3][1].substr(1,string_nodes[i][3][1].length-2));

	                }else if(string_nodes[i].length==3){ // Nodo intermedio
	                    nodes.add({
	                        id: string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2),
	                        label: string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2)+"\n(H="+string_nodes[i][2][1]+")",
	                        title: Number(string_nodes[i][2][1]), //Heuristica del nodo
	                        color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
	                    });
	                    node_heuristics.push(Number(string_nodes[i][2][1]));
	                    potentials_nodes.push(string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2));
	                	//alert("Nodos normales: \nID: "+string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2)+"\nLABEL: "+string_nodes[i][0][1].substr(1,string_nodes[i][0][1].length-2)+"\n(H="+string_nodes[i][2][1]+")"+"\nHEURISTICA: "+Number(string_nodes[i][2][1])+"\nCOLOR: {background:\'#97C2FC\', border:\'#2B7CE9\',highlight:{background:\'#D2E5FF\',border:\'#2B7CE9\'}}");
	                }
	            
	            }else{ //Nodo intermedio modificado por los eventos MODIFICAR AQUI SI SE AÑADEN COSAS AL COLOR EN LOS EVENTOS
	            	string_nodes[i]=string_nodes[i].split("{");
	            	node_color="{"+string_nodes[i][1]+"{"+string_nodes[i][2];

	            	var features=string_nodes[i][0].substr(0,string_nodes[i][0].length-1);
	            	features=features.split(",");
	            	features.splice(-1,1); //Elimino el ultimo elemento, la palabra "color"

	            	for(var j=0; j<features.length; j++) {
	            		features[j]=features[j].split(":")[1];
	            	}
	            	
	            	nodes.add({
	                    id: features[0].substr(1,features[0].length-2),
	                    label: features[0].substr(1,features[0].length-2)+"\n(H="+features[2]+")",
	                    title: Number(features[2]), //Heuristica del nodo
	                    color: {background:'#97C2FC', border:'#2B7CE9',highlight:{background:'#D2E5FF',border:'#2B7CE9'}}
	                });
	                node_heuristics.push(Number(features[2]));
	                potentials_nodes.push(features[0].substr(1,features[0].length-2));

	                //alert("Nodos PRO: \nID: "+features[0].substr(1,features[0].length-2)+"\nLABEL: "+features[0].substr(1,features[0].length-2)+"\n(H="+features[2]+")"+"\nHEURISTICA: "+Number(features[2])+"\nCOLOR: {background:\'#97C2FC\', border:\'#2B7CE9\',highlight:{background:\'#D2E5FF\',border:\'#2B7CE9\'}}");

	            }

	        }
	        //-----------------------------------FIN IMPORTACION DE NODOS----------------------------------//

	        if(potential_initial!=this.imported_initial_node){ //Compruebo si el nodo inicial se corresponde con la realidad
	        	alert("El archivo no ha podido interpretarse: el nodo inicial ha sido manipulado");
	        	return undefined;
	        }


	        for(i=0;i<potentials_end.length;i++){ //Compruebo si los nodos finales se corresponden con la realidad
	        	if(!this.imported_end_nodes.includes(potentials_end[i])){ //Compruebo si el nodo inicial se corresponde con la realidad
	        		alert("El archivo no ha podido interpretarse: los nodos finales han sido manipulados"); //Los nodos finales han sido manipulados
	        		return undefined;
	        	}
	        }

	        //---------------------------------INICIO IMPORTACION DE ARISTAS---------------------------------//
	        var string_edges=this.imported_edges.substr(1, this.imported_edges.length-2).split("}, ");
	        var nedges=string_edges.length;
	    
	        for(var i=0; i<nedges; i++) {
	            if(i==nedges-1){
	                string_edges[i]=string_edges[i].substr(1, string_edges[i].length-2);    
	            }else{
	                string_edges[i]=string_edges[i].substr(1, string_edges[i].length-1);
	            }


	            string_edges[i]=string_edges[i].split(",");

	            for(var j=0; j<string_edges[i].length; j++) {
	                string_edges[i][j]=string_edges[i][j].split(":")
	            }

	            if(string_edges[i].length==4){ //Arista bidireccional 
	                if(!(potentials_nodes.includes(string_edges[i][0][1].substr(1,string_edges[i][0][1].length-2)) && potentials_nodes.includes(string_edges[i][1][1].substr(1,string_edges[i][1][1].length-2)))){
	                	alert("El archivo no ha podido interpretarse: faltan nodos."); //Los nodos finales han sido manipulados
	        			return undefined;
	                }
	                edges.add({
	                    from: string_edges[i][0][1].substr(1,string_edges[i][0][1].length-2),
	                    to: string_edges[i][1][1].substr(1,string_edges[i][1][1].length-2),
	                    id: string_edges[i][2][1].substr(1,string_edges[i][2][1].length-2),
	                    label: Number(string_edges[i][3][1])
	                });


	                //alert("Edges normales: \nFROM: "+string_edges[i][0][1].substr(1,string_edges[i][0][1].length-2)+"\nTO: "+string_edges[i][1][1].substr(1,string_edges[i][1][1].length-2)+"\nID: "+string_edges[i][2][1].substr(1,string_edges[i][2][1].length-2)+"\nLABEL: "+Number(string_edges[i][3][1]));
	            }else if(string_edges[i].length==5){ //Arista dirigida
	            	if(!(potentials_nodes.includes(string_edges[i][0][1].substr(1,string_edges[i][0][1].length-2)) && potentials_nodes.includes(string_edges[i][1][1].substr(1,string_edges[i][1][1].length-2)))){
	                	alert("El archivo no ha podido interpretarse: faltan nodos."); //Los nodos finales han sido manipulados
	        			return undefined;
	                }
	                edges.add({
	                    from: string_edges[i][0][1].substr(1,string_edges[i][0][1].length-2),
	                    to: string_edges[i][1][1].substr(1,string_edges[i][1][1].length-2),
	                    id: string_edges[i][2][1].substr(1,string_edges[i][2][1].length-2),
	                    label: Number(string_edges[i][3][1]),
	                    arrows: string_edges[i][4][1].substr(1,string_edges[i][4][1].length-2)
	                });
	                //alert("Edges normales: \nFROM: "+string_edges[i][0][1].substr(1,string_edges[i][0][1].length-2)+"\nTO: "+string_edges[i][1][1].substr(1,string_edges[i][1][1].length-2)+"\nID: "+string_edges[i][2][1].substr(1,string_edges[i][2][1].length-2)+"\nLABEL: "+Number(string_edges[i][3][1])+"\nARROWS: "+string_edges[i][4][1].substr(1,string_edges[i][4][1].length-2));
	            }

	        }
	        //-----------------------------------FIN IMPORTACION DE ARISTAS----------------------------------//

	        //-----------------------------------IDENTIFICACION NODO INICIAL---------------------------------//
	        var initial_node_id=this.imported_initial_node;
	        //initial_exists=(initial_node_id!=null);
	        //---------------------------------FIN IDENTIFICACION NODO INICIAL-------------------------------//


	        //----------------------------------IDENTIFICACION NODOS FINALES---------------------------------//
	        var end_nodes_id=[];
	        this.imported_end_nodes=this.imported_end_nodes.substr(1,this.imported_end_nodes.length-2).split(", ");
	        for(var i=0; i<this.imported_end_nodes.length; i++){
	            this.imported_end_nodes[i]=this.imported_end_nodes[i].substr(1,this.imported_end_nodes[i].length-2);
	            end_nodes_id.push(this.imported_end_nodes[i]);
	        }
	        //--------------------------------FIN IDENTIFICACION NODOS FINALES-------------------------------//

	        this.grafo_principal.setContent("network",nodes,edges,node_heuristics,initial_node_id,end_nodes_id);
	 		this.is_initial_selected=false;
            this.resetForm();
            //if(!this.created_events){
            this.createNetworkEvents();
            //}
            this.printInfo();

            //Ocultamos el cuadro de importar y dibujar
            $("#network-form-div").hide();
			$("#import-network-div").hide();

			//ponemos el submenu de generar y tal
			$("#submenu").fadeIn("slow");
	    }catch (err) {
	        //alert("El fichero de entrada no tiene una sintaxis interpretable o bien el archivo esta ya cargado.");
	    	alert(err);
	    }

	}











































	//export_network(){}
	//show_div_generate_heuristic(){}
	//go_resolution_mode(){}
	//close_resolution_mode(){}


	solveNetwork(){
		var iter_bound=parseInt(document.getElementById("max_iter_bound").value);
		
		if(!this.grafo_principal.initialNodeExists()){
	    	alert("Debe haber uno (y solo uno) nodo inicial");
	    }else if(this.grafo_principal.getEndNodesId().length==0){
	    	alert("Debe haber al menos un nodo final");
	    }else if(this.grafo_principal.getNumNodes()==0){
	        alert("No existen nodos finales.");
	    }else if(this.grafo_principal.getNumEdges()==0){
	        alert("No existen aristas.");
	    }else if(isNaN(iter_bound)){
	    	alert("Por favor, introduzca un valor numérico entre 1 y 1000 en el campo número máximo de iteraciones.");
	    }else if(iter_bound<1 || iter_bound>Number(document.getElementById("max_iter_bound").max)){
	    	alert("Por favor, introduzca un numero máximo de iteraciones, entre 1 y 1000.");
	    }else{
	        var e = document.getElementById("algorithm-select");
	        var strUser = e.options[e.selectedIndex].value;
	        switch(strUser) {
	            case "deep-search":
	            	//alert("Has elegido Busqueda en profundidad.");
	            	try{
		            	this.resolution=this.algorithms.deepSearch(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Búsqueda en profundidad.";
	                break;
	            case "astar":
	            	//alert("Has elegido A*.");
	                try{
		            	this.resolution=this.algorithms.astar(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: A*.";
	                break;

	           	case "wide-search":
	           		//alert("Has elegido Busqueda en anchura.");
	           		try{
		            	this.resolution=this.algorithms.wideSearch(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Búsqueda en anchura.";
	                break;

				case "retroactive-search":
					//alert("Has elegido Busqueda retroactiva.");
					try{
		            	this.resolution=this.algorithms.retroactiveSearch(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Búsqueda retroactiva.";
	                break;

				case "iterative-descent":
					//alert("Has elegido Descenso iterativo.");
					try{
		            	this.resolution=this.algorithms.iterativeDescent(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Descenso iterativo.";
	                break;

				case "uniform-cost":
					//alert("Has elegido Busqueda de costo uniforme.");
					try{
		            	this.resolution=this.algorithms.uniformCost(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Búsqueda de costo uniforme.";
	                break;


				case "simple-climbing":
					//alert("Has elegido Escalada simple.");
					try{
		            	this.resolution=this.algorithms.simpleClimbing(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Escalada simple.";
	                break;

				case "max-climbing":
					//alert("Has elegido Escalada por la maxima pendiente.");
					try{
		            	this.resolution=this.algorithms.maxClimbing(this.grafo_principal.getNodes(),
		            								this.grafo_principal.getEdges(),
		            								this.grafo_principal.getInitialNodeId(),
		            								this.grafo_principal.getEndNodesId(),
		            								iter_bound);
	                }catch(err){
	                	alert(err);
	                }
	                document.getElementById("act-estate-algorithm-name").textContent="Estado actual del grafo: Escalada por la maxima pendiente.";
	                break;
	        }

	        $("#select-algorithm").fadeOut("fast");
	    	$("#control-buttons").fadeIn("slow");
	    	$("#heuristic-generation").hide();
	    	this.index_step=0;
	    	this.grafo_solucion.setContent_solution("solution_network",this.resolution.steps[this.index_step]);
	    	document.getElementById('textarea-explanation').value=this.resolution.descriptions[this.index_step];
	        document.getElementById('textarea-openclosed').value=this.resolution.lists[this.index_step];

	    }
	}
	

	solutionStepForward(){
		if(this.index_step<this.resolution.descriptions.length-1){
			this.index_step+=1;
			this.grafo_solucion.setContent_solution("solution_network",this.resolution.steps[this.index_step]);
	    	document.getElementById('textarea-explanation').value=this.resolution.descriptions[this.index_step];
	        document.getElementById('textarea-openclosed').value=this.resolution.lists[this.index_step];
		}
	}

	solutionStepBack(){
		if(this.index_step>0){
			this.index_step-=1;
			this.grafo_solucion.setContent_solution("solution_network",this.resolution.steps[this.index_step]);
	    	document.getElementById('textarea-explanation').value=this.resolution.descriptions[this.index_step];
	        document.getElementById('textarea-openclosed').value=this.resolution.lists[this.index_step];
		}
	}

	solutionFirstStep(){
		if(this.index_step!=0){
			this.index_step=0;
			this.grafo_solucion.setContent_solution("solution_network",this.resolution.steps[this.index_step]);
	    	document.getElementById('textarea-explanation').value=this.resolution.descriptions[this.index_step];
	        document.getElementById('textarea-openclosed').value=this.resolution.lists[this.index_step];
		}
	}

	solutionLastStep(){
		var lstep=this.resolution.descriptions.length-1;
		if(this.index_step!=lstep){
			this.index_step=lstep;
			this.grafo_solucion.setContent_solution("solution_network",this.resolution.steps[this.index_step]);
	    	document.getElementById('textarea-explanation').value=this.resolution.descriptions[this.index_step];
	        document.getElementById('textarea-openclosed').value=this.resolution.lists[this.index_step];
		}
	}

	//backToSelectAlgorithm(){}
	//admisible_heur_change(){}
	generateHeuristic(){
		if(this.is_initial_selected){
	    		alert("Por favor, seleccione el nuevo nodo inicial.");
		}else{
			if(!this.grafo_principal.initialNodeExists()){
		    	alert("Debe haber uno (y solo uno) nodo inicial");
		    }else if(this.grafo_principal.getEndNodesId().length==0){
		    	alert("Debe haber al menos un nodo final");
		    }else if(this.grafo_principal.getNumNodes()==0){
		        alert("No existen nodos finales.");
		    }else if(this.grafo_principal.getNumEdges()==0){
		        alert("No existen aristas.");
		    }else if(document.getElementById("min-changes-bound").value == "" && document.getElementById("max-changes-bound").value == "" && !document.getElementById("cb_admisible_heur").checked){
            	alert("Debe introducir valores en los campos de rango si desea generar una heuristica que genere cambios en cerrados.");
		    }else{

	        	var min_cambios=parseInt(document.getElementById("min-changes-bound").value);
	        	var max_cambios=parseInt(document.getElementById("max-changes-bound").value);

	        	var max_intentos=100;
	            var generar_admisible=document.getElementById("cb_admisible_heur").checked; //Miramos a ver si se quiere una heur admisible o no
	            var heuristica_generada;
	            if(generar_admisible){//SE DESEA GENERAR UNA HEURISTICA ADMISIBLE
	            	try{
		            	heuristica_generada=this.algorithms.getNewHeuristic(	this.grafo_principal.getNodes(),
		            														this.grafo_principal.getEdges(),
		            														this.grafo_principal.getInitialNodeId(),
		            														this.grafo_principal.getEndNodesId(),
		            														min_cambios,
		            														max_cambios,
		            														max_intentos,
		            														generar_admisible);
	            	}catch(err){alert(err);}
		            if(heuristica_generada.changes<0){
		            	alert(
		            		this.grafo_principal.getNodeIds().toSource()+"\n"+heuristica_generada.heur.toSource()+".\nSe ha encontrado una heuristica ADMISIBLE, pero no se puede encontrar un camino al final."
		            	);
		            	this.grafo_principal.updateHeuristics(this.grafo_principal.getNodeIds(),heuristica_generada.heur);
		            }else if(heuristica_generada!=null){
		            	alert(this.grafo_principal.getNodeIds().toSource()+"\n"+heuristica_generada.heur.toSource()+".\nEsta heuristica ES ADMISIBLE. provocará "+heuristica_generada.changes+" actualizaciones en cerrados para el algoritmo A*.");
		            	this.grafo_principal.updateHeuristics(this.grafo_principal.getNodeIds(),heuristica_generada.heur);
		            	//$("#heuristic-generation").fadeOut("slow");
		            }else{
		            	alert("No ha sido posible encontrar una heuristica que cumpla los requisitos.\nPuede probar de nuevo con los mismos parametros. Si no se consigue encontrar la heuristica, debería plantearse cambiar el rango del numero de actualizaciones que desea provocar.");
		            }


	            }else{//SE DESEA GENERAR UNA HEURISTICA QUE GENERE CAMBIOS
	            	if(!isNaN(min_cambios) && !isNaN(min_cambios)){
			            if(min_cambios<=max_cambios && min_cambios>=0){
				            try{
					            heuristica_generada=this.algorithms.getNewHeuristic(	this.grafo_principal.getNodes(),
			            															this.grafo_principal.getEdges(),
			            															this.grafo_principal.getInitialNodeId(),
			            															this.grafo_principal.getEndNodesId(),
			            															min_cambios,
			            															max_cambios,
			            															max_intentos,
			            															generar_admisible);
				            }catch(err){alert(err);}
				            if(heuristica_generada!=null){
					            if(heuristica_generada.changes<0){
					            	alert(
					            		this.grafo_principal.getNodeIds().toSource()+"\n"+heuristica_generada.heur.toSource()+".\nSe ha encontrado una heuristica ADMISIBLE, pero no se puede encontrar un camino al final."
					            	);
					            	this.grafo_principal.updateHeuristics(this.grafo_principal.getNodeIds(),heuristica_generada.heur);
				            	}else /*if(heuristica_generada!=null)*/{
					            	alert(this.grafo_principal.getNodeIds().toSource()+"\n"+heuristica_generada.heur.toSource()+".\nEsta heuristica provocará "+heuristica_generada.changes+" actualizaciones en cerrados para el algoritmo A*.");
					            	this.grafo_principal.updateHeuristics(this.grafo_principal.getNodeIds(),heuristica_generada.heur);
					            	//$("#heuristic-generation").fadeOut("slow");
					            }
					        }else{
								alert("No ha sido posible encontrar una heuristica que cumpla los requisitos.\nPuede probar de nuevo con los mismos parametros. Si no se consigue encontrar la heuristica, debería plantearse cambiar el rango del numero de actualizaciones que desea provocar.");      	
					        }
			            }else{
			            	alert("El rango de actualizaciones no es válido. El número mínimo de actualizaciones debe ser mayor o igual que 0 y menor o igual que el número máximo");
			            }
			        }else{
			        	alert("Por favor, introduzca valores numéricos enteros en los campos de número mínimo y máximo de cambios.");
			        }
	            }
	            this.printInfo();
			}
		}
	}

	






	initialization(){
		$("#import-network-input").val("");
		$("#submenu").hide();
		//Resetear el formulario de dibujar cuando se recarga la pagina:
		this.resetForm();
		
	    //FIN RESETEO FORMULARIO
		$("#resolution").hide();
		$("#import-network-btn").prop("disabled",true);
		
		//$("#import-network-input").bind("change",this.readSingleFile.bind(this));
		//document.getElementById('import-network-input').addEventListener('change', this.readSingleFile.bind(this), false);
		$("#import-network-input").on("change",$.proxy(this.readSingleFile,this)); //Ligamos la funcion readSingleFile al contexto this(Interface_Handler)


		$("#close-resolution-mode").hide();
		$("#heuristic-generation").hide();


		$("#network-form-div").hide();
		$("#import-network-div").hide();


		$("#despliegue_dibujar").click(function(){
			$("#import-network-div").hide();
			$("#network-form-div").toggle("slow");
			$("#heuristic_generation").hide();
			$("#resolution").hide();
			//Si cierro el apartado de resolucion tengo que volver a activar el modulo para ir a resolver grafo
			$("#end-network").fadeIn("slow");
			$("#close-resolution-mode").fadeOut("slow");
		});

		$("#despliegue_importar").click(function(){
			$("#network-form-div").hide();
			$("#import-network-div").toggle("slow");
			$("#heuristic_generation").hide();
			$("#resolution").hide();
			//Si cierro el apartado de resolucion tengo que volver a activar el modulo para ir a resolver grafo
			$("#end-network").fadeIn("slow");
			$("#close-resolution-mode").fadeOut("slow");
		});

	}





	resetNodeEntry(){
		$("#node-id").val("");
		$("#node-heuristic").val("");

		if(!this.grafo_principal.initialNodeExists()){//Si el nodo inicial NO existe
			$("#cb_initial_node").attr("disabled", false);
			$("#cb_initial_node").attr("checked", false);
		}else{
			$("#cb_initial_node").attr("disabled", true);
			$("#cb_initial_node").attr("checked", false);
		}

		$("#cb_final_node").attr("disabled", false);
		$("#cb_final_node").attr("checked", false);
	}



	resetEdgeEntry(){
	      $("#edge-from").val("");
	      $("#edge-to").val("");
	      $("#edge-cost").val("");
	      $("#cb_directed_edge").attr("disabled", false);
	      $("#cb_directed_edge").attr("checked", false);
	}


	resetForm(){
		this.resetNodeEntry();
		this.resetEdgeEntry();
	}



	goResolutionMode(){
		if(!this.grafo_principal.initialNodeExists()){
	    	alert("Debe haber uno (y solo uno) nodo inicial");
	    }else if(this.grafo_principal.getEndNodesId().length==0){
	    	alert("Debe haber al menos un nodo final");
	    }else if(this.grafo_principal.getNumNodes()==0){
	        alert("No existen nodos finales.");
	    }else if(this.grafo_principal.getNumEdges()==0){
	        alert("No existen aristas.");
	    }else{
	        //Damos paso a la interfaz de resolucion con jQuery
	        
	        //$("#principal").fadeOut("slow");
	        $("#end-network").fadeOut("slow");
	        $("#resolution").fadeIn("slow");
	        $("#select-algorithm").fadeIn("fast");
	        
	        $("#control-buttons").hide();

	        $("#close-resolution-mode").fadeIn("slow");
	        $("#heuristic-generation").hide();

	        //Ocultamos el cuadro de importar y dibujar
            $("#network-form-div").hide();
			$("#import-network-div").hide();
	    }
	}

	closeResolutionMode(){
	      $("#control-buttons").hide();
	      $("#select-algorithm").fadeIn("fast");
	      $("#resolution").fadeOut("slow");
	      //$("#principal").fadeIn("slow");
	      $("#end-network").fadeIn("slow");
	      $("#close-resolution-mode").fadeOut("slow");
	      //$("#import-network-input").val("");
	      //$("#import-network-div").hide();
	      $("#heuristic-generation").hide();
	}



	backToSelectAlgorithm(){
	      $("#control-buttons").fadeOut("fast");
	      $("#select-algorithm").fadeIn("slow");
	      $("#textarea-explanation").val("");
	      $("textarea-openclosed").val("");
	      $("#heuristic-generation").hide();
	}



	showDivGenerateHeuristic(){
		$("#resolution").fadeOut("slow");
		$("#heuristic-generation").toggle("slow");
		$("#principal").fadeIn("slow");
		$("#end-network").fadeIn("slow");
		$("#close-resolution-mode").fadeOut("slow");

		//Ocultamos el cuadro de importar y dibujar
        $("#network-form-div").hide();
		$("#import-network-div").hide();
	}


	admisibleHeurChange(){
	      var state=document.getElementById("cb_admisible_heur").checked;
	      document.getElementById("min-changes-bound").disabled = state;
	      document.getElementById("max-changes-bound").disabled = state;
	}

	printInfo(){
		document.getElementById("rest-of-data-div").innerHTML=this.grafo_principal.getDescription();
	}


	createNetworkEvents(){
		var net=this.grafo_principal.getNetwork();
		net.on("click", params => {
			//alert("Evento de dar click");
			params.event = "[original event]";
			
			var heuristics=this.grafo_principal.getNodeHeuristics();
			var node_ids=this.grafo_principal.getNodeIds();
			var initial_node_id=this.grafo_principal.getInitialNodeId();
			var end_nodes_id=this.grafo_principal.getEndNodesId();

			if(params.nodes[0]!=null){ //Se ha pinchado un nodo
				this.resetEdgeEntry();

				$("#node-id").val(params.nodes[0]);
	    		var heur_nodo=heuristics[node_ids.indexOf(params.nodes[0])]
	    		$("#node-heuristic").val(heur_nodo);

	    		if (initial_node_id==params.nodes[0]){
	    			$("#cb_initial_node").attr("checked", true);
	    			$("#cb_final_node").attr("checked", false);
	    		}else if(end_nodes_id.includes(params.nodes[0])){
	    			$("#cb_initial_node").attr("checked", false);
	    			$("#cb_final_node").attr("checked", true);
	    		}else{
	    			$("#cb_initial_node").attr("checked", false);
	    			$("#cb_final_node").attr("checked", false);
	    		}

				
				if(this.is_initial_selected){//Estamos esperando cambio, inicial seleccionado
					if(end_nodes_id.includes(params.nodes[0])){//Si un nodo es final y se pincha el con el inicial seleccionado, da error.
						alert("Un nodo final no puede ponerse como inicial.");
					}else{
						//alert("Nodo pinchado: "+params.nodes[0]+", con heuristica "+heur_nodo+". Queda DEseleccionado");	
						this.grafo_principal.updateNode(params.nodes[0],heuristics[node_ids.indexOf(params.nodes[0])],true,false);
						this.is_initial_selected=false;
					}
					$("#cb_initial_node").attr("checked", true);
					$("#cb_final_node").attr("checked", false);
					//alert("Nodo pinchado: "+params.nodes[0]+", con heuristica "+heur_nodo+". Queda DEseleccionado");	
				}else if(params.nodes[0]==initial_node_id){ //Si se ha pinchado en el nodo inicial sin que estuviera seleccionado, queda seleccionado
					//this.is_initial_selected=true;
					//alert("Nodo pinchado: "+params.nodes[0]+", con heuristica "+heur_nodo+". Queda seleccionado");
					this.grafo_principal.setColorNodeSelected(initial_node_id);
					this.is_initial_selected=true;
					//alert("Nodo pinchado: "+params.nodes[0]+", con heuristica "+heur_nodo+". Queda seleccionado");
				}
				
				this.printInfo();
			}else if(params.edges[0]!=null){
				this.resetNodeEntry();
				var edge_data = this.grafo_principal.getEdges().get({
				  fields: ['id','from','to','label','arrows'],    // output the specified fields only
				});
				
				for(var i=0;i<edge_data.length;i++){
					if(edge_data[i].id == params.edges[0]){
						$("#edge-from").val(edge_data[i].from);
						$("#edge-to").val(edge_data[i].to);
						$("#edge-cost").val(Number(edge_data[i].label));
						if(edge_data[i].arrows=="to"){
							$("#cb_directed_edge").attr("checked", true);
						}

						break;
					}
				}
			}else{ //QUEDA QUE SE DESELECCIONE EL INICIAL
				//alert("Nodo inicial: "+initial_node_id);
				if(this.grafo_inicial.initialNodeExists()){
					this.grafo_principal.setColorNodeInitial(initial_node_id);
					this.is_initial_selected=false;
					this.resetForm();
				}
			}
			//alert(params.edges[0]+""+params.nodes[0]);
			//alert(params.edges[0]==null+""+params.nodes[0]==null);
			
		});




		//Con doble click se ponen los nodos finales
		net.on("doubleClick", params => {
			//alert("Evento de dar doble click");
			params.event = "[original event]";

			var heuristics=this.grafo_principal.getNodeHeuristics();
			var node_ids=this.grafo_principal.getNodeIds();
			var initial_node_id=this.grafo_principal.getInitialNodeId();
			var end_nodes_id=this.grafo_principal.getEndNodesId();
			
			if(params.nodes[0]==initial_node_id){
				alert("El nodo inicial no puede ser final.");
			}else{
				//Si el nodo ya era final, deja de ser final.
				if(end_nodes_id.includes(params.nodes[0])){
					this.grafo_principal.updateNode(params.nodes[0],heuristics[node_ids.indexOf(params.nodes[0])],false,false);
				}else if(params.nodes[0]!=null){//Si el nodo no es final, pasa a ser final
					this.grafo_principal.updateNode(params.nodes[0],heuristics[node_ids.indexOf(params.nodes[0])],false,true);
				}
			}

			this.printInfo();
		});




		this.created_events=true;
		//alert("Eventos creados");
	}
}