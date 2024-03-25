%%%this Matlab Program script the user to Explore different Fractals. Fundamentally, this program implements a
%%%class-like structure to generate different fractals


%ToDo: Cache the last saved window, so that it can quickly be restored...
% Default Values
resolution = 400; %%Initial Resolution


prog = 1; %Identify the Fractal (Either Mandelbrot or Julia)
tour = [-1 0;0.3 0.6;0.285 0.01;-0.835 -0.2321; -0.0300 -0.6908]; %%A stack of Locations (classic Julia Sets) on the Tour. Format R,C
history = [1 0 0 0 0 0 0 0]; %Store a history buffer of past scenes, so we can return to them

%Internal Variables
CR = 0;
CC = 0;
repl = 1;
lowerx = -2;
lowery = -2;
upperx = 2;
uppery = 2;
range = 4;
pending = 0;

%in the first REPL, the user needs to select the general operating mode,
%either Mandelbrot or Julia


disp('Welcome to the Fast Fractal Explorer (FFE from now on), made by Sam McDiarmid-Sterling ')
message = sprintf("The program is optimized to maintain a resolution of %dx%d pixels. This setting may be altered by changing the value of the resolution variable in FractalExplorer.m", resolution, resolution);
disp(message)
while repl
    i = input('FFE>>>',"s");
    switch i
        case 'Mandelbrot'
            disp('Mandelbrot:');
            prog = 1;
            repl = 0;
            history = [prog -2 2 -2 2 ((upperx-lowerx)/resolution) 0 0];
        case 'Julia'
            m_args = input('Julia: \n Enter Starting Real and Imaginary Values: CR,CC: ',"s");
            a = sscanf(m_args,'%f,%f');
             if a
                CR = a(1);
                CC = a(2);
            else    
                CR = -.79;
                CC = 0.15;
            end
            prog = 2;
            history = [prog -2 2 -2 2 ((upperx-lowerx)/resolution) CR CC];
            repl = 0;
        case 'e'
            repl=0;
            disp('Goodbye');
            return;
        case 'q'
            repl=0;
            disp('Goodbye');
            return;
        otherwise
            disp('Valid commands are:');
            disp('Mandelbrot');
            disp('Julia');
            disp('e (or q) to exit');

    end
end


step = ((upperx-lowerx)/resolution);

%display the initial view
Set(prog,CR,CC, lowerx,upperx, lowery,uppery,step,4)

%in the second repl, the user interacts with the set, 
repl_1 = 1;
while repl_1 
    
    
    fprintf('Current Bounds %d:x:%d, %d:y:%d \n',lowerx,upperx,lowery,uppery);
    disp('z:zoom r:resolution e:exit');
    keypress = waitforbuttonpress();
    Key=get(gcf,'CurrentKey');
    
    switch Key
        case 't' %the guided julia set tour
            prog = 2; %this is used in the Julia setting
            disp('Popping off the tour stack')
             [m,n] = size(tour);
             %retrieve the first row off the stack
              CR = tour(1,1);
              CC = tour(1,2);

             if m>1
                tour(1,:) = []; %delete the top of the stack...
             end
        case 'v' %switch view between mandelbrot and julia sets
            if prog == 1 %currently in mandelbrot view
                [bx,by] = ginput(1);
                disp(bx);
                disp(by);
                prog = 2;
                CR = bx;
                CC = by;
                lowerx = -2;
                upperx = 2;
                lowery = -2;
                uppery = 2;
                [m,n] = size(history);
                if m<5 %only allow the history buffer to store a maximum of five elements
                history = [[prog,lowerx,upperx,lowery,uppery,step,CR,CC]; history]; %add to the top of the stack
                else
                     history = [[prog,lowerx,upperx,lowery,uppery,step,CR,CC]; history]; %add to the top of the stack
                     history(6,:) = []; %push onto the stack, delte the oldest entry
                end
            else %%reveal the julia set in the mandelbrot view
                prog = 1;
                lowerx = -2;
                upperx = 2;
                lowery = -2;
                uppery = 2;
                [m,n] = size(history);
                if m<5 %only allow the history buffer to store a maximum of five elements
                history = [[prog,lowerx,upperx,lowery,uppery,step,CR,CC]; history]; %add to the top of the stack
                else
                     history = [[prog,lowerx,upperx,lowery,uppery,step,CR,CC]; history]; %add to the top of the stack
                     history(6,:) = []; %push onto the stack, delte the oldest entry
                end
                pending = 1;
            end
        case 'u' %pop off the history stack
             disp('Popping off the stack')
             [m,n] = size(history);
             %retrieve the first row off the stack
              prog   = history(2,1);
              lowerx = history(2,2);
              upperx = history(2,3);
              lowery = history(2,4);
              uppery = history(2,5);
              step   = history(2,6);

             if m>2
                history(2,:) = []; %delete the top of the stack...
             end
        case 'z' %zoom
             disp('Select a point in the lower left and one in the upper right to begin ')
             disp("Zooming...")
             [bx,by] = ginput(2);
             disp(bx);
             disp(by);
             lx_t = lowerx;
             ly_t = lowery;
             lowerx = min(bx(1),bx(2));
             lowery = min(by(1),by(2));
             upperx = max(bx(2),bx(1));
             uppery = max(by(1),by(2));
    
             range = max(upperx-lowerx,uppery-lowery);
             step = ((range)/resolution);
             disp('lowerx is ');
             disp(lowerx);
             disp('upperx is ');
             disp(upperx);
             disp('lowery is ');
             disp(lowery);
             disp('uppery is ');
             disp(uppery);
             %add to the history stack
             [m,n] = size(history);
             if m<5 %only allow the history buffer to store a maximum of five elements
                history = [[prog,lowerx,upperx,lowery,uppery,step,0,0]; history]; %add to the top of the stack
             else
                 history = [[prog,lowerx,upperx,lowery,uppery,step,0,0]; history]; %add to the top of the stack
                 history(6,:) = []; %push onto the stack, delte the oldest entry
             end

        case 'r' %reset the resolution
             resolution = input('enter the new resolution ');
             
             if ~(resolution)
                 disp('Error, resoltion not found');
                 resolution = 1000;
             end
             step = ((range)/resolution);
        case 'h' %help message
            disp('z:zoom r:resolution e:exit u: pop off the zoom stack, returning up views v: switch views t: next stop in the guided tour');
        case 'e' %exit
            repl_1 = 0;
            return;
    end
    Set(prog,CR,CC,lowerx,upperx, lowery,uppery,step,range);
    if pending
                %add a marker in the image if switching from julia to
                %mandelbrot
        hold on;
        plot(CR,CC, "k-s", "MarkerFaceColor","b","MarkerSize",15);
        hold off;
        pending = 0;
    end


end

function Set(prog,CR,CC,lowerx,upperx,lowery,uppery,step,range) 
    c = Interface(prog,lowerx,upperx, lowery, uppery, step,CR,CC);%%The C program returns a one dimensional array (of size l*l,1)
    l = sqrt(length(c)); %%reshape the array 
    final = reshape(c,[l l]);
    imagesc([lowerx upperx],[lowery uppery],final)
    if prog == 2
        disp(CR);
        disp(CC);
    end
 
end
