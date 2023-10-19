#include "WebServ.hpp"

std::string HttpResponseUtils::testResponse(HttpStatusCode statusCode, std::string body) {
    std::stringstream responseStream;
    responseStream << "HTTP/1.1 " << statusCode << " " << getStatus(Ok) << "\r\n";
    responseStream << "Content-Type: text/html\r\n";
    responseStream << "\r\n"; // Fin de las cabeceras, línea en blanco
    responseStream << body.c_str();

    return responseStream.str();
}

void    HttpResponseUtils::initStatusMap(void) {
    if(HttpResponseUtils::statusMap.empty()) {
        HttpResponseUtils::statusMap.insert(std::make_pair(Ok, "OK"));
        HttpResponseUtils::statusMap.insert(std::make_pair(Created, "Created"));
        HttpResponseUtils::statusMap.insert(std::make_pair(NotFound, "Not Found"));
        HttpResponseUtils::statusMap.insert(std::make_pair(BadRequest, "Bad Request"));
        HttpResponseUtils::statusMap.insert(std::make_pair(MethodNotAllowed, "Method Not Allowed"));
        HttpResponseUtils::statusMap.insert(std::make_pair(RequestEntityTooLarge, "Request Entity Too Large"));
        HttpResponseUtils::statusMap.insert(std::make_pair(RequestUriTooLong, "Request-URI Too Long"));
        HttpResponseUtils::statusMap.insert(std::make_pair(VersionNotSupported, "Version Not Supported"));
        HttpResponseUtils::statusMap.insert(std::make_pair(InternalServerError, "Internal Server Error"));
    }
}

std::string HttpResponseUtils::getStatus(HttpStatusCode responseCode) {
    std::map<HttpStatusCode, std::string>::iterator it = HttpResponseUtils::statusMap.find(responseCode);
    if (it != HttpResponseUtils::statusMap.end()) {
        return (it->second);
    }
    return (NULL);
}

std::string HttpResponseUtils::errorBody(HttpStatusCode responseCode) {
    std::ostringstream error;

    std::ostringstream response;
    response << "<!DOCTYPE html>";
    response << "<html>";
    response <<     "<head>";
    response <<         "<title>" << (responseCode != Ok ? "Error " : "" ) << responseCode << "</title>";
    response <<         "<style>";
    response <<             "@import url(https://fonts.googleapis.com/css?family=Open+Sans);html{background-color:#fefefe}body{font-family:Open Sans,Arial;color:#454545;font-size:16px;margin:2em auto;max-width:800px;padding:1em;line-height:1.4;text-align:justify}html.contrast body{color:#050505}html.contrast blockquote{color:#11151a}html.contrast blockquote:before{color:#262626}html.contrast a{color:#0051c9}html.contrast a:visited{color:#7d013e}html.contrast span.wr{color:#800}html.contrast span.mfw{color:#117e69}html.inverted{background-color:#010101}html.inverted body{color:#bababa}html.inverted div#invmode{color:#fff;background-color:#000}html.inverted blockquote{color:#dad0c7}html.inverted blockquote:before{color:#bfbfbf}html.inverted a{color:#07a}html.inverted a:visited{color:#ac5a82}html.inverted span.wr{color:#c0392b}html.inverted span.mfw{color:#19b496}a{color:#07a}a:visited{color:#941352}.noselect{-webkit-touch-callout:none;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}span.citneed{vertical-align:top;font-size:.7em;padding-left:.3em}small{font-size:.4em}p.st{margin-top:-1em}div.fancyPositioning div.picture-left{float:left;width:40%;overflow:hidden;margin-right:1em}div.fancyPositioning div.picture-left img{width:100%}div.fancyPositioning div.picture-left p.caption{font-size:.7em}div.fancyPositioning div.tleft{float:left;width:55%}div.fancyPositioning div.tleft p:first-child{margin-top:0}div.fancyPositioning:after{display:block;content:"";clear:both}ul li img{height:1em}blockquote{color:#456;margin-left:0;margin-top:2em;margin-bottom:2em}blockquote span{float:left;margin-left:1rem;padding-top:1rem}blockquote author{display:block;clear:both;font-size:.6em;margin-left:2.4rem;font-style:oblique}blockquote author:before{content:"- ";margin-right:1em}blockquote:before{font-family:Times New Roman,Times,Arial;color:#666;content:open-quote;font-size:2.2em;font-weight:600;float:left;margin-top:0;margin-right:.2rem;width:1.2rem}blockquote:after{content:"";display:block;clear:both}@media screen and (max-width:500px){body{text-align:left}div.fancyPositioning div.picture-left,div.fancyPositioning div.tleft{float:none;width:inherit}blockquote span{width:80%}blockquote author{padding-top:1em;width:80%;margin-left:15%}blockquote author:before{content:"";margin-right:inherit}}span.visited{color:#941352}span.visited-maroon{color:#85144b}span.wr{color:#c0392b;font-weight:600;text-decoration:underline}div#contrast{color:#000;top:10px}div#contrast,div#invmode{cursor:pointer;position:absolute;right:10px;font-size:.8em;text-decoration:underline;-webkit-touch-callout:none;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}div#invmode{color:#fff;background-color:#000;top:34px;padding:2px 5px}span.sb{color:#00e}span.sb,span.sv{cursor:not-allowed}span.sv{color:#551a8b}span.foufoufou{color:#444;font-weight:700}span.foufoufou:before{content:"";display:inline-block;width:1em;height:1em;margin-left:.2em;margin-right:.2em;background-color:#444}span.foufivfoufivfoufiv{color:#454545;font-weight:700}span.foufivfoufivfoufiv:before{content:"";display:inline-block;width:1em;height:1em;margin-left:.2em;margin-right:.2em;background-color:#454545}span.mfw{color:#16a085}a.kopimi,a.kopimi img.kopimi{display:block;margin-left:auto;margin-right:auto}a.kopimi img.kopimi{height:2em}p.fakepre{font-family:monospace;font-size:.9em}";
    response <<             "html{";
    response <<                 "background-color: #e74c3c;";
    response <<                 "display: flex;";
    response <<                 "align-items: center;";
    response <<                 "justify-content: center;";
    response <<                 "height: 100vh;";
    response <<             "}";
    response <<             "body{";
    response <<                 "color: #fefefe;";
    response <<                 "display: flex;";
    response <<                 "align-items: center;";
    response <<                 "justify-content: center;";
    response <<             "}";
    response <<             ".error-middle{";
    response <<                 "display: block;";
    response <<                 "vertical-align: middle;";
    response <<             "}";
    response <<             "h1{";
    response <<                 "color: black;";
    response <<             "}";
    response <<         "</style>";
    response <<     "</head>";
    response <<     "<body>";
    response <<         "<div class=\"error-middle\">";
    response <<             "<h1>" << (responseCode != Ok ? "Error " : "" ) << responseCode << " - " << getStatus(responseCode) << "</h1>";
    response <<         "</div>";
    response <<     "</body>";
    response << "</html>";
    return (response.str());
}