#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#define TAILLE_MAX 200
/*--------------------------------------IMPORTANT - ORDRE DU CSV---------------------------------------------------



redtag - id - d - height - width - x - y - fill - fontsize - style - stroke - stroke-width - points - cx - cy - node - r - heading - bound1 - bound2 - edgeNameFromXPlane - pathLength - radius - slope - type - latitude - longitude - twy - angle - exit-edge - node-cx - node-cy

//CTRL + MAJ + /

-----------------------------------------------------------------------------------------------------------------*/
//Flags for the fprintf instruction (writing in the csv)
int f_id;
int f_d;
int f_height;
int f_width;
int f_x;
int f_y;
int f_fill;
int f_fontsize;
int f_style;
int f_stroke;
int f_stroke_width;
int f_points;
int f_cx;
int f_cy;
int f_node_;
int f_r;
int f_heading;
int f_bound1;
int f_bound2;
int f_edgeNameFromXPlane;
int f_pathLength;
int f_radius;
int f_slope;
int f_type;
int f_latitude;
int f_longitude;
int f_twy;
int f_angle;
int f_exit_edge;
int f_node_cx;
int f_node_cy;

//Fields' value, for each line
char* id;
char* d;
char* height;
char* width;
char* x;
char* y;
char* fill;
char* fontsize;
char* style;
char* stroke;
char* stroke_width;
char* points;
char* cx;
char* cy;
char* node_;
char* r;
char* heading;
char* bound1;
char* bound2;
char* edgeNameFromXPlane;
char* pathLength;
char* radius;
char* slope;
char* type;
char* latitude;
char* longitude;
char* twy;
char* angle;
char* exit_edge;
char* node_cx;
char* node_cy;
//Binary condition to check if the the element that is being treated belongs to the same tag as the one before
int wewerehere=0;

void reset(){
  //Reset values

   id="";
   d="";
   height="";
   width="";
   x="";
   y="";
   fill="";
   fontsize="";
   style="";
   stroke="";
   stroke_width="";
   points="";
   cx="";
   cy="";
   node_="";
   r="";
   heading="";
   bound1="";
   bound2="";
   edgeNameFromXPlane="";
   pathLength="";
   radius="";
   slope="";
   type="";
   latitude="";
   longitude="";
   twy="";
   angle="";
   exit_edge="";
   node_cx="";
   node_cy="";
   //Reset the flags
   f_id=0;
   f_d=0;
   f_height=0;
   f_width=0;
   f_x=0;
   f_y=0;
   f_fill=0;
   f_fontsize=0;
   f_style=0;
   f_stroke=0;
   f_stroke_width=0;
   f_points=0;
   f_cx=0;
   f_cy=0;
   f_node_=0;
   f_r=0;
   f_heading=0;
   f_bound1=0;
   f_bound2=0;
   f_edgeNameFromXPlane=0;
   f_pathLength=0;
   f_radius=0;
   f_slope=0;
   f_type=0;
   f_latitude=0;
   f_longitude=0;
   f_twy=0;
   f_angle=0;
   f_exit_edge=0;
   f_node_cx=0;
   f_node_cy=0;
}

void update(FILE* csv,xmlNode* node){

  xmlAttr* elems = node->properties;
  while(elems)
  {
    xmlChar* value0 = xmlNodeListGetString(node->doc, elems->children, 1);
    //printf("\n type [%s] le nom [%s] le contenu [%s]" ,node->name,elems->name,value0);
    if(strcmp((char*)elems->name,"id")==0){
      id= (char*) value0;
      f_id=1;
    }
    if(strcmp((char*)elems->name,"d")==0){
      d=(char*) value0;
      f_d=1;
    }
    if(strcmp((char*)elems->name,"height")==0){
      height= (char*) value0;
      f_height=1;
    }
    if(strcmp((char*)elems->name,"width")==0){
      width= (char*) value0;
      f_width=1;
    }
    if(strcmp((char*)elems->name,"x")==0){
      x= (char*) value0;
      f_x=1;
    }
    if(strcmp((char*)elems->name,"y")==0){
      y= (char*) value0;
      f_y=1;
    }
    if(strcmp((char*)elems->name,"fill")==0){
      fill= (char*) value0;
      f_fill=1;
    }
    if(strcmp((char*)elems->name,"fontsize")==0){
      fontsize= (char*) value0;
      f_fontsize=1;
    }
    if(strcmp((char*)elems->name,"style")==0){
      style= (char*) value0;
      f_style=1;
    }
    if(strcmp((char*)elems->name,"stroke")==0){
      stroke= (char*) value0;
      f_stroke=1;
    }
    if(strcmp((char*)elems->name,"stroke-width")==0){
      stroke_width= (char*) value0;
      f_stroke_width=1;
    }
    if(strcmp((char*)elems->name,"points")==0){
      points= (char*) value0;
      f_points=1;
    }
    if(strcmp((char*)elems->name,"cx")==0){
      cx= (char*) value0;
      f_cx=1;
    }
    if(strcmp((char*)elems->name,"cy")==0){
      cy= (char*) value0;
      f_cy=1;
    }
    if(strcmp((char*)elems->name,"node")==0){
      node_= (char*) value0;
      f_node_=1;
    }
    if(strcmp((char*)elems->name,"r")==0){
      r= (char*) value0;
      f_r=1;
    }
    if(strcmp((char*)elems->name,"heading")==0){
      heading= (char*) value0;
      f_heading=1;
    }
    if(strcmp((char*)elems->name,"bound1")==0){
      bound1= (char*) value0;
      f_bound1=1;
    }
    if(strcmp((char*)elems->name,"bound2")==0){
      bound2= (char*) value0;
      f_bound2=1;
    }
    if(strcmp((char*)elems->name,"edgeNameFromXPlane")==0){
      edgeNameFromXPlane= (char*) value0;
      f_edgeNameFromXPlane=1;
    }
    if(strcmp((char*)elems->name,"pathLength")==0){
      pathLength= (char*) value0;
      f_pathLength=1;
    }
    if(strcmp((char*)elems->name,"radius")==0){
      radius= (char*) value0;
      f_radius=1;
    }
    if(strcmp((char*)elems->name,"slope")==0){
      slope= (char*) value0;
      f_slope=1;
    }
    if(strcmp((char*)elems->name,"type")==0){
      type= (char*) value0;
      f_type=1;
    }
    if(strcmp((char*)elems->name,"latitude")==0){
      latitude= (char*) value0;
      f_latitude=1;
    }
    if(strcmp((char*)elems->name,"longitude")==0){
      longitude= (char*) value0;
      f_longitude=1;
    }
    if(strcmp((char*)elems->name,"twy")==0){
      twy= (char*) value0;
      f_twy=1;
    }
    if(strcmp((char*)elems->name,"angle")==0){
      angle= (char*) value0;
      f_angle=1;
    }
    if(strcmp((char*)elems->name,"exit-edge")==0){
      exit_edge= (char*) value0;
      f_exit_edge=1;
    }

    if(strcmp((char*)elems->name,"node-cx")==0){
      node_cx= (char*) value0;
      f_node_cx=1;
    }
    if(strcmp((char*)elems->name,"node-cy")==0){
      node_cy= (char*) value0;
      f_node_cy=1;
    }
    elems = elems->next;

    wewerehere=1;
  }
  if(wewerehere){
    char buffer[2048];
    //On traite l'entiereté de l'attribut comme une seule chaîne de caractères
    #define WRITE(attribut) \
        snprintf(buffer, sizeof(buffer), "\"%s\"", attribut); \
        fwrite(buffer, strlen(buffer), 1, csv); \
        fwrite(",",1,1,csv);

    //Pour le dernier élément
    #define WRITEF(attribut) \
        snprintf(buffer, sizeof(buffer), "\"%s\"", attribut); \
        fwrite(buffer, strlen(buffer), 1, csv); \
        fwrite("\n",1,1,csv);

    //Pour l'élément style; There is no style
    #define WRITES(attribut) \
        fwrite("", 1, 1, csv); \
        fwrite(",",1,1,csv);

    //printf("\nles flags id %d [%s] et node-cx %d [%s]",f_id,id,f_node_cx,node_cx);
    WRITE(id);
    WRITE((char*) node->name);
    WRITE(d);
    WRITE(height);
    WRITE(width);
    WRITE(x);
    WRITE(y);
    WRITE(fill);
    WRITE(fontsize);
    WRITES(style);
    WRITE(stroke);
    WRITE(stroke_width);
    WRITE(points);
    WRITE(cx);
    WRITE(cy);
    WRITE(node_);
    WRITE(r);
    WRITE(heading);
    WRITE(bound1);
    WRITE(bound2);
    WRITE(edgeNameFromXPlane);
    WRITE(pathLength);
    WRITE(radius);
    WRITE(slope);
    WRITE(type);
    WRITE(latitude);
    WRITE(longitude);
    WRITE(twy);
    WRITE(angle);
    WRITE(exit_edge);
    WRITE(node_cx);
    WRITEF(node_cy);

    //fprintf(csv,"%s, %s, %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s,  %s \n",id,(char*) node->name,d,height,width,x,y,fill,fontsize,style,stroke,stroke_width,points,cx,cy,node_,r,heading,bound1,bound2,edgeNameFromXPlane,pathLength,radius,slope,type,latitude,longitude,twy,angle,exit_edge,node_cx,node_cy);
    reset();
  }

}

//Fonction de listage de tous les red tags sous un noeud
void verifyRedTag(xmlNode* node){
  if (node == NULL) {
      fprintf(stderr, "Tags not found, the node doesn't exist...\n");
      return;
  }
  xmlAttr* elems = node->properties;
  xmlChar* value0 = xmlNodeListGetString(node->doc, elems->children, 1);
    //printf("\n type [%s] le nom [%s] le contenu [%s]" ,node->name,elems->name,value0);
  char* category="";
  for (xmlNode *child = node->children; child; child = child->next){
    if(child->type==1)
      printf("%s\n",(char*)child->name);
    }
}

//Fonction de listage de toutes les catégories sous le noeud
void verifyCategory(xmlNode* node){
  if (node == NULL) {
      fprintf(stderr, "Categories not found, the node doesn't exist...\n");
      return;
  }
  xmlAttr* elems = node->properties;
  for (xmlNode *child = node->children; child; child = child->next){
    if(child->children!=NULL){
      xmlAttr* elems_child = child->properties;
      xmlChar* value00 = xmlNodeListGetString(child->doc,elems_child->children, 2);
      if(child->parent==node && strcmp((char*)elems_child->name,"id")==0)
        printf("\n%s\n ",value00);
    }
    else{
      xmlAttr* elemss = child->properties;
      while(elemss)
      {
        xmlChar* value0 = xmlNodeListGetString(child->doc, elemss->children, 1);
        if(strcmp((char*)elemss->name,"id")==0)
        printf("\n%s\n ",value0);
        elemss = elemss->next;
      }
    }
  }
}

void updateToWrite(FILE* csv,xmlNode* node,int sameline){
  wewerehere=0;
  update(csv,node);
  if(!(node->children==NULL)){
    //printf("\n%s",xmlNodeListGetString(node->doc, node->properties->children, 1));
    for (xmlNode *child = node->children; child; child = child->next){
      updateToWrite(csv,child,0);
    }
  }

}

//Vérifier l'existance du noeud et le renvoyer
xmlNode *search(xmlNode *node, const char *id) {
    for (xmlNode *current = node; current; current = current->next) {
        if (current->type == XML_ELEMENT_NODE && xmlStrcmp(current->name, (const xmlChar *)"g") == 0) {
            xmlChar *prop = xmlGetProp(current, (const xmlChar *)"id");
            if (prop && xmlStrcmp(prop, (const xmlChar *)id) == 0) {
                xmlFree(prop);
                return current;
            }
            xmlFree(prop);
        }
        xmlNode *found = search(current->children, id);
        if (found) return found;
    }
    return NULL;
}


void parse_xml_to_csv(const char *xml_file, const char *csv_file) {
    LIBXML_TEST_VERSION

    xmlDoc *document = xmlReadFile(xml_file, NULL, 0);
    if (document == NULL) {
        fprintf(stderr, "Failed to parse %s\n", xml_file);
        return;
    }

    xmlNode *root = xmlDocGetRootElement(document);
    if (root == NULL) {
        fprintf(stderr, "Empty XML\n");
        xmlFreeDoc(document);
        return;
    }
    //To initialize the values
    reset();

    //Vérification existance ==> write: xmlNode* x = search(root,"x") with x the node's id (example : ParkingPositionElement)
    //Please note that the node must have children, otherwise there is nothing to display
    xmlNode *layer1 = search(root, "layer1");

    // AirportBoundary
    //
    // TaxiwayGuidanceLine
    //
    // ParkingGuidanceLine
    //
    // RIMCAS
    //
    // Runways90m
    //
    // RunwayThreshold
    //
    // ParkingPositionElement
    //
    // HoldingPoints
    //
    //Routing
    //
    // ExitRunways
    //Début Partie instanciation csv
    FILE *csv = fopen(csv_file, "w");
    if (csv == NULL) {
        perror("Couldn't open CSV");
        xmlFreeDoc(document);
        return;
    }
    fprintf(csv," id, type , d, height, width, x, y, fill, fontsize, style, stroke, stroke-width, points, cx, cy, node, r, heading, bound1, bound2, edgeNameFromXPlane, pathLength, radius, slope, type, latitude, longitude, twy, angle, exit-edge, node-cx, node-cy");
    fprintf(csv,"\n");
    //Fin Partie instanciation csv

    //Here, you'll have the choice between calling three different functions:
    //verifyCategory to display the node's children categories (AirportBoundary,path_airport_boundary ...)
    //verifyTags to display the node's children tags (g,circle,rect,path ...)
    //updateToWrite to convert the svg into a csv file
      //printf("Les catégories:\n");
      //verifyCategory(layer1);
      //printf("Les Tags:\n");
      //verifyRedTag(layer1);
      //verifyCategory(taxiway);
      //printf("<airportbounda>\n");
      //updateToWrite(csv, taxiway,0);
      //printf("\n</airportbounda>\n");
      //printf("<taxiway>\n");
      //ecriture(csv, taxiwayGuidanceLine, "TaxiwayGuidanceLine");
      //printf("\n</taxiway>\n");
      updateToWrite(csv,layer1,0);
      //updateToWrite(csv,parking,0);
      //updateToWrite(csv,routing);
      //updateToWrite(csv,exit,0);
    //Fin Tests




    fclose(csv);
    xmlFreeDoc(document);
    xmlCleanupParser();
    printf("OK -> %s\n", csv_file);
    //Fin Partie instanciation csv
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_xml> <output_csv>\n", argv[0]);
        return EXIT_FAILURE;
    }
    reset();
    parse_xml_to_csv(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
