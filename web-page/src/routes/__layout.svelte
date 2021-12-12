<script lang="ts">
	import globalCss from '../global.css';
</script>

<svelte:head>
	<link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon.png" />
	<link rel="icon" type="image/png" sizes="32x32" href="/favicon-32x32.png" />
	<link rel="icon" type="image/png" sizes="16x16" href="/favicon-16x16.png" />
	<link rel="manifest" href="/manifest.json" />
	<link rel="mask-icon" href="/safari-pinned-tab.svg" color="#191a19" />
	<meta name="msapplication-TileColor" content="#00a300" />
	<meta name="theme-color" content="#191a19" />
	<meta name="apple-mobile-web-app-capable" content="yes" />
	<meta name="mobile-web-app-capable" content="yes" />
	<meta name="description" content="Interface da Horta Inteligente" />
	<link rel="stylesheet" href={globalCss} />
	<title>Horta Inteligente</title>
</svelte:head>
<main>
	<slot />
</main>

<style>
	main {
		display: flex;
		flex-direction: column;
		justify-content: center;
		justify-items: center;
		background: var(--primary-color-1);
		margin: auto;
		max-width: 1024px;
		width: 100%;
		height: 100%;
		text-align: center;
		padding: 20px;
		padding-top: 0;
	}
</style>
