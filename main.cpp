////////////////////////////////////////////////////////////////////////////////
//
// (C) Juanmi Huertas Delgado 2014
//
// This is supposed to be a Physics Game with Panchito as protagonist
//
// Enabling Bullet Physics!
//
#define OCTET_BULLET 1

#include "../../octet.h"

#include "PanchitoJog.h"

/// Create a box with octet
int main(int argc, char **argv) {
  // path from bin\Debug to octet directory
  octet::app_utils::prefix("../../../");

  // set up the platform.
  octet::app::init_all(argc, argv);

  // our application.
  octet::PanchitoJog app(argc, argv);
  app.init();

  // open windows
  octet::app::run_all_apps();
}


