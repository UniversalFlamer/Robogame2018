classdef (Abstract)routePlanning
    properties
        graph
        route %Returned value of inverse dynamics as Planned Route 
        direction % n*2 matrix ,every 2-dimensional vector represents a movement.
        % move format:
        % [int{1 for Sarm,2 for Barm,3 for Parm} int{Steps}]
    end
    methods
        function obj = routePlanning(graph)
            obj.graph=graph;
        end
    end
        
    methods (Abstract)
        calculateRoute(arg)
        %Calculate ideal route%
        showAnimation(arg)
        %show a clip of animation of the route% 
        calculateDirection(arg)
        %{convert route to the real control parametres of step motors,considering the correction of inaccuracy caused by our robot amrs}%
        calculateAmendment(arg)
        %{real time correction}%
    end
end

    
        
        
    
    
        
        
    
