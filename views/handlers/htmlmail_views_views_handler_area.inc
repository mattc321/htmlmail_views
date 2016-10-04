<?php
//htmlmail_views_handler_area_autorefresh

/**
 * Base class for area handlers.
 *
 * @ingroup views_area_handlers
 */
class htmlmail_views_views_handler_area extends views_handler_area {

  /**
   * Overrides views_handler_area::init().
   *
   * Reset override done in views_handler_area::init(). This area must be
   * rendered even if view has no results.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
  }

  function option_definition() {
	$site_email = variable_get('site_mail', '');
    $options = array();
	$options['htmlmail_views_option'] = array('default' => TRUE, 'bool' => TRUE);
	$options['htmlmail_views_from_user'] = array('default' => FALSE, 'bool' => TRUE);
    $options['htmlmail_views_from_alias'] = array('default' => $site_email);
    $options['htmlmail_views_link_text'] = array('default' => 'Email this View');
    $options['htmlmail_views_def_recipient'] = array('default' => '');
    $options['htmlmail_views_body_msg'] = array('default' => '');
    $options['htmlmail_views_global_css'] = array('default' => '');
    $options['htmlmail_views_def_subject'] = array('default' => '');
    $options['htmlmail_views_other_view'] = array('default' => '');
    // $options['sourceSelector'] = array('default' => '.view-content');
    // $options['afterSelector'] = array('default' => '.view-header');
    // $options['targetStructure'] = array('default' => '<div class="view-content"></div>');
    // $options['oddClass'] = array('default' => 'views-row-odd');
    return $options;
  }

  function options_form(&$form, &$form_state) {
	  //incremental
	  //interval
	  $form['htmlmail_views_option'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable htmlmail_views'),
	  '#description' => t('Enabling this will allow this view or another view to be emailed from this display.</br><em>Anyone with access to this view will have the ability to email it.</em>'),
      '#default_value' => $this->options['htmlmail_views_option'],
    );
	$form['htmlmail_views_other_view'] = array(
      '#type' => 'textfield',
      '#title' => t('Email a Different View'),
	  '#description' => t('You can optionally embed a different view or display other than this one. The Email Link will still be visible on this display.</br><strong>If this field is populated it will be the only view sent in the email.</strong><em>(syntax: view_name|display_name)</em>'),
      '#default_value' => $this->options['htmlmail_views_other_view'],
    );
	$form['htmlmail_views_link_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link Text'),
      '#required' => TRUE,
	  '#description' => t('The clickable link that will display in the view header'),
      '#default_value' => $this->options['htmlmail_views_link_text'],
    );
    $form['htmlmail_views_from_alias'] = array(
      '#type' => 'textfield',
      '#title' => t('Default From: Alias'),
	  '#description' => t('The site email will be used for sending emails. Leave blank to use "no-reply@"'),
      '#default_value' => $this->options['htmlmail_views_from_alias'],
    );
	$form['htmlmail_views_from_user'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use the Current User\'s Email'),
	  '#description' => t('Use the currently logged in user\'s email address as the senders email by default.'),
      '#default_value' => $this->options['htmlmail_views_from_user'],
    );
	$form['htmlmail_views_def_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Default Subject'),
	  '#description' => t('Subject text to appear by default. Users will still be prompted for a subject.'),
      '#default_value' => $this->options['htmlmail_views_def_subject'],
    );
	$form['htmlmail_views_def_recipient'] = array(
      '#type' => 'textfield',
      '#title' => t('Default To: Recipient'),
	  '#description' => t('Email address for the default recipient(s) separated by comma. Users will still be prompted for an email.'),
      '#default_value' => $this->options['htmlmail_views_def_recipient'],
    );
	 $form['htmlmail_views_body_msg'] = array(
      '#type' => 'textarea',
      '#title' => t('Default Body Message'),
	  '#description' => t('The default message used in the email body before the view is inserted.</br><em>You may use HTML and CSS</em>'),
      '#default_value' => $this->options['htmlmail_views_body_msg'],
    );
	$form['htmlmail_views_global_css'] = array(
      '#type' => 'textarea',
      '#title' => t('Global CSS'),
	  '#description' => t('Additional CSS to apply to all emails. Use this only for styling html tags. All other styles should be inline.'),
      '#default_value' => $this->options['htmlmail_views_global_css'],
    );
  }

  function options_validate(&$form, &$form_state) {
	
//{+} VAL EMAIL
	$email_raw = $form_state['values']['options']['htmlmail_views_def_recipient'];
	$elist = explode(",", $email_raw);
	foreach ($elist as $key => $email) {
		$email = trim($email);
		if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
			form_set_error('htmlmail_views_def_recipient', t('Invalid email format.'));
		}		
	}
	
//{+} VAL OTHER VIEW
	$otherview = $form_state['values']['options']['htmlmail_views_other_view'];
	$otherview = explode("|", $otherview);
	if (!views_get_view($otherview[0], $otherview[1])) {
		form_set_error('htmlmail_views_other_view', t('Invalid view format or view display not found.'));
	}
	
  }
	
	// /**
   // * Don't run a query
   // */
  // function query() { }
  
  function render($empty = FALSE) {
	//rendering is handled by hook_preprocess_views_ in module
	$vname = $this->view->name;
	$dname = $this->view->current_display;
	
	$crend = '<div id="htmlmail-views-link">';
	$crend .= $this->options['htmlmail_views_link_text'];
	$crend .= '</div>';
	
	return $crend;
	
  }
}
