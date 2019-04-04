classdef graph
    properties
        origin_coordinates %n*2 matrix%
        %DO BE AWARE THAT coordinates are supposed to be IN ORDER!
        corrected_coordinates %n*2 matrix%
    end
    methods
        function obj=graph(origin_coordinates)
            if(length(origin_coordinates)==2)
                obj.origin_coordinates=origin_coordinates;
            else
                disp("WRONG PARAMETRES IN graph£ºWRONG DIMENSION OF MATRIX OF origin_coordinates ")
            end  
        end
        function correct(obj,arm_origin_vector,area_ratio) %arm_origin_vector 1*2
            if height(arm_origin_vector)==1 && length(arm_origin_vector)==2 
                if isnumeric(area_ratio)
                    for i=1:length(obj.origin_coordinates)
                        obj.origin_coordinates(i,1)=obj.origin_coordinates(i,1)*area_ratio+arm_origin_vector(1,1);
                        obj.origin_coordinates(i,2)=obj.origin_coordinates(i,2)*area_ratio+arm_origin_vector(1,2);
                    end
                else
                    disp("WRONG PARAMETRES IN correct:AREA RATIO REQUIRED TO BE NUMERIC")
                end
            else
                disp("WRONG PARAMETRES IN correct:WRONG DIMENSION OF MATRIX OF arm_origin_vector")
            end
                        
                        
                    
                
            
            
        end
    end
end

        
