classdef connectToArduino
    properties
        connection=arduino()
    end
    methods
        function obj=connectToArduino(port,board_type)
            obj.connection=arduino(port,board_type);
        end
        function obj=sendDirection(obj)
        end
        function obj=getCurrentStatus(obj)
        end
        function obj=move(obj)
        end
    end
    methods(Abstract)
        getDirection(obj)
    end
        
end