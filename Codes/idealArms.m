classdef idealArms < arms&connectToArduino&routePlanning
    properties  
        arm_origin_vector
        %{ Relative position of graph coordinates system and arm origin-centred system}%
        robot_arm        
    end
    methods
        function obj=idealArms(L1,L2,arm_origin_vector)
            obj@arms(L1,L2);
            if(isvector(arm_origin_vector))
                obj.arm_origin_vector=arm_origin_vector;
            else
                disp("WRONG PARAMETRES IN idealArms：VECTOR REQUIRED FOR INITIALISATION!")
            end
            %Initialise robot_arm as "RigidBodyTree"%
            obj.robot_arm = robotics.RigidBodyTree('DataFormat','column','MaxNumBodies',3);
            body = robotics.RigidBody('link1');
            joint = robotics.Joint('joint1', 'revolute');
            setFixedTransform(joint,trvec2tform([0 0 0]));
            joint.JointAxis = [0 0 1];
            body.Joint = joint;
            addBody(obj.robot_arm, body, 'base');
            
            body = robotics.RigidBody('link2');
            joint = robotics.Joint('joint2','revolute');
            setFixedTransform(joint, trvec2tform([L1,0,0]));
            joint.JointAxis = [0 0 1];
            body.Joint = joint;
            addBody(obj.robot_arm, body, 'link1');
            
            body = robotics.RigidBody('tool');
            joint = robotics.Joint('fix1','fixed');
            setFixedTransform(joint, trvec2tform([L2, 0, 0]));
            body.Joint = joint;
            addBody(obj.robot_arm, body, 'link2');
            
        end
        function showRobotArm(obj)
            showdetails(obj.robot_arm)
        end
        function obj=graphInitialisation(graph,arm_origin_vector,area_ratio) %To be refined ?  
            obj.graph=graph;
            obj.graph.correct(arm_origin_vector,area_ratio);
        end
        function calculateRoute(obj)
            if obj.graph.isComplete()==1
                route_3d = [graph.corrected_coordinates;zeros(length(graph.corrected_coordinates),1)];
                
                %下面这段是从官方代码2-D Path Tracing With Inverse Kinematics中抄（改编）的，我真的没完全看懂官方的英语文档在干啥(/ω＼) 所以就先这样吧 我尽量写了注释了>_<%
                count=length(graph.corrected_coordinates);
                    %点的数量%
                q0 = homeConfiguration(robot);
                    %存放初始的机械臂位置参数%
                ndof = length(q0);
                qs = zeros(count, ndof);
                    %初始化存放两个机械臂的角度的矩阵%
                ik = robotics.InverseKinematics('RigidBodyTree', robot);
                    %初始化逆运动学solver并使用默认的BFGSGradientProjection算法（BFGS梯度投影算法？）%
                weights = [0, 0, 0, 1, 1, 0];
                    %这个weight上好像是设定机械臂的目标坐标的允差？之后这里应该可以调%
                    %前三个坐标是描述orientation error的允差，后三个描述距离目标坐标允差的%
                endEffector = 'tool';
                    %设定机械臂的作用器 对于我们的机械臂是笔 也就是机械小臂的末端%
                qInitial=q0;
                %设定初始状态的机械臂%
                for i = 1:count
                    point=route_3d(i,:);
                    %取出轨迹中第i个坐标%
                    qSol = ik(endEffector,trvec2tform(point),weights,qInitial);
                    %利用求解器求解：从机械臂的作用器（endEffector）从当前状态（qInitial）到下一个状态（由目标坐标转换为的transformation矩阵描述的解），基于weights所描述的允差范围内%
                    qs(i,:) = qSol;
                    %存储解%
                    qInitial = qSol;
                    %更新机械臂状态%
                end
                
                
                
            else
                disp("graph OBJECT IS NOT COMPLETE TO SERVE AS A TRAJECTORY!")
            end
        end
        function showAnimation(obj)
            
        end
        function calculateDirection(obj)
            
        end
    end
end
            
        
        
        
            
            
            
            
    
        
             
        
        
        
            
            
            
            
    
        
        
