/* Always include this in all plug-ins */
#include <libgimp/gimp.h>

/* The name of my PDB procedure */
#define PLUG_IN_PROC "plug-in-amrmath-c-demo-hello-world"

/* Our custom class HelloWorld is derived from GimpPlugIn. */
struct _HelloWorld
{
  GimpPlugIn parent_instance;
};

#define HELLO_WORLD_TYPE (hello_world_get_type())
G_DECLARE_FINAL_TYPE (HelloWorld, hello_world, HELLO_WORLD,, GimpPlugIn)


/* Declarations */
static GList          * hello_world_query_procedures (GimpPlugIn           *plug_in);
static GimpProcedure  * hello_world_create_procedure (GimpPlugIn           *plug_in,
                                                      const gchar          *name);

static GimpValueArray * hello_world_run              (GimpProcedure        *procedure,
                                                      GimpRunMode           run_mode,
                                                      GimpImage            *image,
                                                      GimpDrawable        **drawables,
                                                      GimpProcedureConfig  *config,
                                                      gpointer              run_data);


G_DEFINE_TYPE (HelloWorld, hello_world, GIMP_TYPE_PLUG_IN)

static void
hello_world_class_init (HelloWorldClass *klass)
{
  GimpPlugInClass *plug_in_class = GIMP_PLUG_IN_CLASS (klass);

  plug_in_class->query_procedures = hello_world_query_procedures;
  plug_in_class->create_procedure = hello_world_create_procedure;
}

static void
hello_world_init (HelloWorld *hello_world)
{
}

static GList *
hello_world_query_procedures (GimpPlugIn *plug_in)
{
  return g_list_append (NULL, g_strdup (PLUG_IN_PROC));
}

static GimpProcedure *
hello_world_create_procedure (GimpPlugIn  *plug_in,
                              const gchar *name)
{
  GimpProcedure *procedure = NULL;

  if (g_strcmp0 (name, PLUG_IN_PROC) == 0)
    {
      procedure = gimp_image_procedure_new (plug_in, name,
                                            GIMP_PDB_PROC_TYPE_PLUGIN,
                                            hello_world_run, NULL, NULL);

      gimp_procedure_set_sensitivity_mask (procedure, GIMP_PROCEDURE_SENSITIVE_ALWAYS);

      gimp_procedure_set_menu_label (procedure, "_C Hello World");
      gimp_procedure_add_menu_path (procedure, "<Image>/Hell_o Worlds/");

      gimp_procedure_set_documentation (procedure,
                                        "Official Hello World Tutorial in C",
                                        "Some longer text to explain about this procedure. "
                                        "This is mostly for other developers calling this procedure.",
                                        NULL);
      gimp_procedure_set_attribution (procedure, "Amr Muhammmad",
                                      "Amr Muhammad, AmrMath project",
                                      "2025");
    }

  return procedure;
}

static GimpValueArray *
hello_world_run (GimpProcedure        *procedure,
                 GimpRunMode           run_mode,
                 GimpImage            *image,
                 GimpDrawable        **drawables,
                 GimpProcedureConfig  *config,
                 gpointer              run_data)
{
  GimpTextLayer *text_layer;
  GimpLayer     *parent   = NULL;
  gint           position = 0;
  gint           n_drawables;

  n_drawables = gimp_core_object_array_get_length ((GObject **) drawables);

  if (n_drawables > 1)
    {
      GError *error = NULL;

      g_set_error (&error, GIMP_PLUG_IN_ERROR, 0,
                   "Procedure '%s' works with zero or one layer.",
                   PLUG_IN_PROC);

      return gimp_procedure_new_return_values (procedure,
                                               GIMP_PDB_CALLING_ERROR,
                                               error);
    }
  else if (n_drawables == 1)
    {
      GimpDrawable *drawable = drawables[0];

      if (! GIMP_IS_LAYER (drawable))
        {
          GError *error = NULL;

          g_set_error (&error, GIMP_PLUG_IN_ERROR, 0,
                       "Procedure '%s' works with layers only.",
                       PLUG_IN_PROC);

          return gimp_procedure_new_return_values (procedure,
                                                   GIMP_PDB_CALLING_ERROR,
                                                   error);
        }

      parent   = GIMP_LAYER (gimp_item_get_parent (GIMP_ITEM (drawable)));
      position = gimp_image_get_item_position (image, GIMP_ITEM (drawable));
    }

  text_layer = gimp_text_layer_new (image, "Hello World!", gimp_context_get_font(),
                                    20.0, gimp_unit_pixel ());
  gimp_image_insert_layer (image, GIMP_LAYER (text_layer), parent, position);

  gimp_message ("DEBUG: Hello World!");

  return gimp_procedure_new_return_values (procedure, GIMP_PDB_SUCCESS, NULL);
}


/* Generate needed main() code */
GIMP_MAIN (HELLO_WORLD_TYPE)
