classdef (Abstract)arms
    properties
        L1
        L2
    end
    properties(Abstract)
        DH_parametres
        robot_arm
    end
    methods
        function obj=arms(L1,L2)
            if(nargin==2)
                if(isnumeric(L1)&&isnumeric(L2))
                    obj.L1=L1;
                    obj.L2=L2;
                else
                    disp("WRONG PARAMETRES IN arms£ºNUMERIC VALUE REQUIRED")
                end
            else
                disp("WRONG NUMBER OF PARAMETRES IN arms")
            end
        end
    end
end
    
        
        
        