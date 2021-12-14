<script lang="ts">
	import { goto } from '$app/navigation';
	let username: string;
	let password: string;
	let disabled = false;
	let invalid = false;

	async function submit() {
		disabled = true;
		invalid = false;
		const response = await fetch('/authenticate', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/x-www-form-urlencoded'
			},
			body: `username=${username}&password=${password}`
		});
		if (response.ok) {
			goto('/');
		} else if (response.status === 401) {
			invalid = true;
		}
	}
</script>

<form on:submit|preventDefault={submit}>
	{#if invalid}
		<p>Usuário ou senha invalido!</p>
	{/if}
	<label for="username">Usuário:</label>
	<input bind:value={username} required type="text" name="username" id="username" class:invalid />
	<label for="password">Senha:</label>
	<input
		bind:value={password}
		required
		type="password"
		name="password"
		id="password"
		class:invalid
	/>
	<button type="submit" {disabled}>Login</button>
</form>

<style>
	.invalid {
		border: solid 2px var(--temperature-color);
	}

	form {
		display: flex;
		height: 100vh;
		flex-direction: column;
		align-content: center;
		justify-content: center;
		max-width: 768px;
		margin: auto;
	}

	p {
		align-self: flex-start;
		color: var(--temperature-color);
		margin-bottom: 8px;
	}

	button {
		background: var(--accent-color);
		border: outset 2px var(--accent-color);
		justify-self: end;
		align-self: flex-start;
	}
	label {
		align-self: flex-start;
		margin-bottom: 4px;
	}

	input {
		width: 100%;
		max-width: 240px;
		color: black;
		height: 32px;
		margin-bottom: 16px;
	}
</style>
