function y = parse(x)

    axes(x.axes1);
    fclose(instrfind)
    s=serial('COM9');
    fopen(s);

    value0=[];
    value1=[];
    value2=[];

    n=0;

    while n<10
        line=fscanf(s);    
        if (isempty(line) == 0) && (line(end)==newline)          
            line=line(1:end-1);
            parsedLine=strsplit(line,',');

            [value0new, value1new, value2new]=parsedLine{1:3};

            value0=[value0; str2num(value0new)];
            value1=[value1; str2num(value1new)];
            value2=[value2; str2num(value2new)];      
            
            plot(value0,value1);
            ylim([0 40])
            drawnow();
            n=n+1;
        end
    end

    fclose(s);
    delete(s);
end