/* Footer HTML */ 

#ifndef HTML_PART_Footer_h
#define HTML_PART_Footer_h

const char PART_Footer_html[] PROGMEM = R"rawliteral(
<div id="footer">
    <div class="columns mt-10">
        <span class="label label-rounded label-blank"></span> 
        <div class="columns mt-8">
        <div class="columns mt-4">
            <div class="col-12 text-center">
            <span class="label label-rounded mr-2">%IDplaceholder%</span> 
            -
            <span class="label label-rounded label-primary ml-2">%processorplaceholder%</span>
            -
            <span class="label label-rounded mr-2">%type%</span> 
            </div>
        </div> 
        <div class="columns mt-8">
            <span class="label label-rounded label-error">%errorplaceholder%</span> 
        </div>
        </div>
    </div>
</div>
)rawliteral";

#endif  // HTML_PART_Footer_h