#include  <gtk/gtk.h>

/* Rotina disparada quando o evento "fechar janela principal" ocorre */
void  on_window_closed (GtkWidget  *Widget ,  gpointer  dados) 
{ 
    gtk_main_quit  (); 
}

/* Rotina disparada quando o evento "botao contador clicado" ocorre */
void  on_botao_clicked(GtkWidget  *thisButton,  GtkWidget  *count) {
	
	static int cont = 0;
	char msg[4];
	
	cont++;
	if (cont>999) cont = 0;
	sprintf(msg, "%d", cont);
	gtk_entry_set_text(GTK_ENTRY(count), msg);
}

int  main(int argc, char *argv []) 
{ 
    GtkWidget  *janela , *botao, *contador, *box;

    /* Inicializar sistema GUI */ 
    gtk_init(& argc, &argv ); 
    
	/* Criar widget Janela */ 
    janela  =  gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* Definir alguns atributos da janela, tamanho inicial, titulo, modo modal, não redimensionavel, como exemplo */
    gtk_window_set_default_size(GTK_WINDOW(janela), 180, 100);
	gtk_window_set_title(GTK_WINDOW(janela), "Exemplo 2");
	gtk_window_set_modal(GTK_WINDOW(janela), TRUE);	
	gtk_window_set_resizable(GTK_WINDOW(janela), FALSE);
    
	/* Associar a rotina de fechar a janela ao evento "fechar a janela" */ 
    g_signal_connect(janela ,  "destroy" ,  G_CALLBACK(on_window_closed),  NULL ); 
    
	/* Criar widget "botao" que ao ser clicado incrementa o campo do widget "contador" */ 
    botao = gtk_button_new_with_label("Contador");		// cria o widget "botao"
    gtk_widget_set_margin_start(botao, 50);				// cria espaço a esquerda do widget
	gtk_widget_set_margin_end(botao, 50);				// cria espaço a direita do widget
	
	/* Criar widget "contador" que mostra o texto da variavel que controla o contador */ 
	contador = gtk_entry_new();                            	// cria o widget "contador"
	gtk_entry_set_width_chars(GTK_ENTRY(contador), 5);		// define o tamanho em caracteres do widget
	gtk_entry_set_alignment(GTK_ENTRY(contador), 0.5);		// alinha o texto mostrado no widget no centro
	gtk_editable_set_editable(GTK_EDITABLE(contador), FALSE);  // define que o widget não sera "editavel"
	gtk_widget_set_margin_start(contador, 75);				// cria espaço a esquerda do widget
	gtk_widget_set_margin_end(contador, 75);				// cria espaço a direita do widget
	gtk_entry_set_text(GTK_ENTRY(contador), "0");			// inicializa o testo do widget com o valor "0"
	
	/* Associar a rotina de incrementar o contador e mostrar ao evento "clicar botao" */ 
	g_signal_connect(botao , "clicked" ,  G_CALLBACK(on_botao_clicked),  contador);
	
	/* Criar o widget vertical "box" e inserir os widgets "botao" e "contador" nele */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(box), contador, TRUE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box), botao, TRUE, FALSE, 5);
	
	/* Criar um "container" na janela principal criada e adicionar o widget "box" */ 
    gtk_container_add(GTK_CONTAINER(janela), box); 
	 
	/* Exibir os widgets "janela" e todos os seus widgets internos  */ 
    gtk_widget_show_all(janela); 
    
	/* Definir foco na janela principal para o widget "botao" ao iniciar a aplicacao */
	gtk_widget_grab_focus(botao);	
	
	/* Ciclo principal de eventos */ 
    gtk_main();

    return(0); 
}