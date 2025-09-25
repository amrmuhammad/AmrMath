/* Always include this in all plug-ins */
#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

/* The name of my PDB procedure */
#define PLUG_IN_PROC "plug-in-amrmath-c-math-text-creator"

/* Our custom class MathTextCreator is derived from GimpPlugIn. */
struct _MathTextCreator
{
  GimpPlugIn parent_instance;
};

#define MATH_TEXT_CREATOR_TYPE (math_text_creator_get_type())
G_DECLARE_FINAL_TYPE (MathTextCreator, math_text_creator, MATH_TEXT_CREATOR,, GimpPlugIn)


/* Declarations */
static GList          * math_text_creator_query_procedures (GimpPlugIn           *plug_in);
static GimpProcedure  * math_text_creator_create_procedure (GimpPlugIn           *plug_in,
                                                      const gchar          *name);

static GimpValueArray * math_text_creator_run              (GimpProcedure        *procedure,
                                                      GimpRunMode           run_mode,
                                                      GimpImage            *image,
                                                      GimpDrawable        **drawables,
                                                      GimpProcedureConfig  *config,
                                                      gpointer              run_data);


G_DEFINE_TYPE (MathTextCreator, math_text_creator, GIMP_TYPE_PLUG_IN)

static void
math_text_creator_class_init (MathTextCreatorClass *klass)
{
  GimpPlugInClass *plug_in_class = GIMP_PLUG_IN_CLASS (klass);

  plug_in_class->query_procedures = math_text_creator_query_procedures;
  plug_in_class->create_procedure = math_text_creator_create_procedure;
}

static void
math_text_creator_init (MathTextCreator *math_text_creator)
{
}

static GList *
math_text_creator_query_procedures (GimpPlugIn *plug_in)
{
  return g_list_append (NULL, g_strdup (PLUG_IN_PROC));
}

static GimpProcedure *
math_text_creator_create_procedure (GimpPlugIn  *plug_in,
                              const gchar *name)
{
  GimpProcedure *procedure = NULL;

  if (g_strcmp0 (name, PLUG_IN_PROC) == 0)
    {
      procedure = gimp_image_procedure_new (plug_in, name,
                                            GIMP_PDB_PROC_TYPE_PLUGIN,
                                            math_text_creator_run, NULL, NULL);

      gimp_procedure_set_sensitivity_mask (procedure, GIMP_PROCEDURE_SENSITIVE_ALWAYS);

      gimp_procedure_set_menu_label (procedure, "_C Math Text Creator");
      gimp_procedure_add_menu_path (procedure, "<Image>/Math Text Creator/");

      gimp_procedure_set_documentation (procedure,
                                        "Math Text Creator plugin written in C",
                                        "Math Text Creator plugin. "
                                        "Math Text Creator plugin. This is mostly for other developers calling this procedure.",
                                        NULL);
      gimp_procedure_set_attribution (procedure, "Amr Muhammmad",
                                      "Amr Muhammad, AmrMath project",
                                      "2025");
                                      
      gimp_procedure_add_font_argument   (procedure, "font", "Font", NULL,
                                          FALSE, NULL, TRUE,
                                          G_PARAM_READWRITE);
      gimp_procedure_add_int_argument    (procedure, "font-size", "Font Size", NULL,
                                          1, 1000, 20,
                                          G_PARAM_READWRITE);
      gimp_procedure_add_unit_argument   (procedure, "font-unit", "Font Unit", NULL,
                                          TRUE, FALSE, gimp_unit_pixel (),
                                          G_PARAM_READWRITE);
      gimp_procedure_add_string_argument (procedure, "text", "Text", NULL,
                                          "Math Text Creator!",
                                          G_PARAM_READWRITE);                                
    }

  return procedure;
}

#define PLUG_IN_BINARY "c-math-text-creator"

static GimpValueArray *
math_text_creator_run (GimpProcedure        *procedure,
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

  gchar         *text;
  GimpFont      *font;
  gint           size;
  GimpUnit      *unit;

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

  if (run_mode == GIMP_RUN_INTERACTIVE)
    {
      GtkWidget *dialog;

      gimp_ui_init (PLUG_IN_BINARY);
      dialog = gimp_procedure_dialog_new (procedure,
                                          GIMP_PROCEDURE_CONFIG (config),
                                          "Math Text Creator");
      gimp_procedure_dialog_fill (GIMP_PROCEDURE_DIALOG (dialog), NULL);
      
      //////////////////////////////////////////////////////////////////////////////////////////////////////
      GtkWidget *view;
      GtkTextBuffer *buffer;

      view = gtk_text_view_new ();

      buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

      gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

      /* Now you might put the view in a container and display it on the
       * screen; when the user edits the text, signals on the buffer
       * will be emitted, such as "changed", "insert_text", and so on.
      */
      //////////////////////////////////////////////////////////////////////////////////////////////////////

      if (! gimp_procedure_dialog_run (GIMP_PROCEDURE_DIALOG (dialog)))
        return gimp_procedure_new_return_values (procedure, GIMP_PDB_CANCEL, NULL);
    }

  g_object_get (config,
                "text",      &text,
                "font",      &font,
                "font-size", &size,
                "font-unit", &unit,
                NULL);

  text_layer = gimp_text_layer_new (image, text, font, size, unit);
  gimp_image_insert_layer (image, GIMP_LAYER (text_layer), parent, position);

  gimp_message ("DEBUG: Math Text Creator!");

  g_clear_object (&font);
  g_clear_object (&unit);
  g_free (text);

  return gimp_procedure_new_return_values (procedure, GIMP_PDB_SUCCESS, NULL);
}



/* Generate needed main() code */
GIMP_MAIN (MATH_TEXT_CREATOR_TYPE)
