<?php

/**
 * Implements hook_views_data_alter().
 */
function htmlmail_views_views_data_alter(&$data) {
   
   $data['views']['enable_htmlmail_views'] = array(
    'title' => t('Enable Html Email'),
    'group' => t('Global'),
    'help' => t('Provided by htmlmail_views module'),
	'area' => array(
      'handler' => 'htmlmail_views_views_handler_area',
	),
  );
}
