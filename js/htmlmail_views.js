(function ($) {
	  Drupal.behaviors.htmlmail_views_behaviours = {
		attach: function (context, settings) {
			
		$(window).load(function() {
			console.log('poop');	
		});
//-----------[+] Success div behavior		
		if ($('.ajax-messages').length > 0) {
			$( "div.ajax-messages" ).fadeIn( 400 ).delay( 2500 ).fadeOut( 800 );
			$('span.pos').click(function() {
				this.parentElement.style.display='none';
			});
		}
    }
  };
})(jQuery);