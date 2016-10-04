(function ($) {
	  Drupal.behaviors.entityform_custom_behaviours = {
		attach: function (context, settings) {
			
		$(window).load(function() {
			console.log('entityform_custom_behaviours module & jquery loaded');	
		});
		
		if ($('.efcb-sniffer').length > 0) {
			$('a.efcb-sniffer').click(function(e) {
				e.preventDefault();
				$('#edit-efcb-attach-form-und-0-value').val(this.id);
				
			});
		}
		if ($('#efcb-see-forms').length > 0) {
			$('#efcb-see-forms').click(function(e) {
				e.preventDefault();
				if (!$('#efcb-avail-forms').is(':visible')) {
					$('#efcb-avail-forms').fadeIn('slow');
				} else {
					$('#efcb-avail-forms').hide();
				}
				
				
				
			});
		}
		
//-----------[+] FUNCTION FOR CLONING ENTITYFORM
		$(function() {
		  // Handler for .ready() called.
		  	var field = 'efcb';
			var url = window.location.href;
			if(url.indexOf('?' + field + '=') != -1) {
				
				//get a random number
				var a = (Math.floor(100000 + Math.random() * 900000)).toString();
				
				//get user input
				var name;
				do {
					name=prompt("Enter a short form name to describe this form. 1 or 2 words.");
					if (name === null) {
						window.location.href = "/admin/structure/entityform_types";
					}
				}
				while(name.length < 4);
				orig_name = 'Form - ' + name;
				//clean the input
				name = name.replace(/[^a-z0-9\s]/gi, '').replace(/\s/g, '');
				
				a = 'form_' + name + '_' + a.substring(-2);
				a = a.toLowerCase();
				$('#edit-type').val(a);
				$('#edit-label').val(orig_name);
				$('#edit-enable-efcb-setting').prop('checked', true);
				$('form#entityform-type-form').submit();
				
			}
		});
//-----------[-] END-----------------------------------		
    }
  };
})(jQuery);